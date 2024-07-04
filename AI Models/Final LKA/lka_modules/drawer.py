from lka_modules.global_variables import *
import cv2
import numpy as np
import datetime
import math

def draw_roi(img, vertices, color=(0, 255, 0), thickness=5):
    """
    Draws the region of interest on the image.

    Parameters:
    - img: The original image.
    - vertices: The vertices of the polygon representing the region of interest.
    - color: The color of the polygon's edges. Default is green.
    - thickness: The thickness of the polygon's edges.
    """
    for i in range(vertices.shape[1] - 1):
        cv2.line(
            img, tuple(vertices[0][i]), tuple(vertices[0][i + 1]), color, thickness
        )
    # Draw a line from the last vertex to the first vertex
    cv2.line(img, tuple(vertices[0][-1]), tuple(vertices[0][0]), color, thickness)
    return img

def get_hconcat_frames(img1, img2):
    img = cv2.hconcat([img1, img2])
    return img

def detect_lines(masked_edges):
    """
    Detects straight lines in the masked, edge-detected image using the Hough Transform algorithm.

    This function converts the edge-detected image into a series of lines, defined by their endpoints.
    Parameters such as the resolution of the accumulator, minimum line length, and maximum gap between
    line segments can be adjusted to optimize detection.

    Parameters:
    - masked_edges: Masked edge-detected image.

    Returns:
    - Lines detected in the image.
    """
    detected_lines = cv2.HoughLinesP(
        masked_edges, 1, np.pi / 180, 50, np.array([]), minLineLength=20, maxLineGap=150
    )

    # cv2.imshow("lines", masked_edges)
    # cv2.waitKey(0)

    return detected_lines

def draw_control_action_arrow(
    img,
    control_action,
    base_position,
    scale=1,
    color=(0, 255, 0),
    thickness=2,
    tip_length=0.5,
):
    """
    Draws an arrow representing the PID control action on the image.

    Parameters:
    - img: The image onto which to draw.
    - control_action: The PID control action value.
    - base_position: A tuple (x, y) representing the base position of the arrow on the image.
    - scale: A scaling factor for the control action to adjust arrow length.
    - color: The color of the arrow (B, G, R).
    - thickness: The thickness of the arrow line.
    - tip_length: The length of the arrow tip in relation to the arrow length.
    """
    end_x = int(base_position[0] + control_action * scale)
    end_y = base_position[1]
    cv2.arrowedLine(
        img, base_position, (end_x, end_y), color, thickness, tipLength=tip_length
    )

def draw_lines(img, bird_view, lines, top_y, bottom_y, offset_file, control_actions_file):
    """
    Draws lines on the image.

    Parameters:
    - img: Original image.
    - lines: Lines to draw.

    Returns:
    - Image with lines drawn.
    """
    global angle_buffer, left_line_buffer, right_line_buffer, previous_time

    left_line_x = []
    left_line_y = []
    right_line_x = []
    right_line_y = []
    detected_left_line = False
    detected_right_line = False

    if lines is not None:
        for line in lines:
            for x1, y1, x2, y2 in line:
                slope = (y2 - y1) / (x2 - x1)
                if abs(slope) < 0.5:  # Filter out horizontal lines
                    continue
                if slope <= 0:  # Left lane
                    left_line_x.extend([x1, x2])
                    left_line_y.extend([y1, y2])
                    detected_left_line = True
                else:  # Right lane
                    right_line_x.extend([x1, x2])
                    right_line_y.extend([y1, y2])
                    detected_right_line = True

    left_x_pos = bird_view.shape[1] * 0.25
    right_x_pos = bird_view.shape[1] * 0.75

    if detected_left_line and left_line_x and left_line_y:
        left_poly = np.polyfit(left_line_y, left_line_x, deg=1)
        left_line_buffer.append(left_poly)
        left_x_pos = np.polyval(left_poly, bottom_y)
    elif left_line_buffer:
        left_poly = left_line_buffer[-1]
        left_x_pos = np.polyval(left_poly, bottom_y)

    if detected_right_line and right_line_x and right_line_y:
        right_poly = np.polyfit(right_line_y, right_line_x, deg=1)
        right_line_buffer.append(right_poly)
        right_x_pos = np.polyval(right_poly, bottom_y)
    elif right_line_buffer:
        right_poly = right_line_buffer[-1]
        right_x_pos = np.polyval(right_poly, bottom_y)

    lane_center = (left_x_pos + right_x_pos) / 2  # This is the center of the lane
    car_position = bird_view.shape[1] / 2  # This is the center of the image
    deviation_pixels = (
        car_position - lane_center
    )  # Positive if car is to the right of the lane center, negative otherwise
    meters_per_pixel = ROAD_WIDTH / (right_x_pos - left_x_pos)
    deviation_meters = deviation_pixels * meters_per_pixel

    # Write the deviation to the offset file
    print(f"Deviation: {deviation_meters:.2f} cm")
    offset_file.write(f"{deviation_meters}\n")

    deviation_direction = "right" if deviation_meters > 0 else "left"
    abs_deviation_meters = abs(deviation_meters)

    # Within the loop, after calculating deviation_meters
    current_time = datetime.datetime.now()
    dt = (current_time - previous_time).total_seconds()
    previous_time = current_time

    # Assuming deviation_meters is the current value you want to correct with PID
    control_action = pid_controller.update(deviation_meters, dt)
    # adjust_motor(control_action)

    # For now, let's just print the control action to see the output
    print(f"Control Action: {control_action}")
    control_actions_file.write(f"{control_action}\n")

    # Draw the control action arrow on the image at the bottom center
    base_position = (
        bird_view.shape[1] // 2,
        bird_view.shape[0] - 30,
    )
    draw_control_action_arrow(
        bird_view,
        control_action,
        base_position,
        scale=10000,
        color=(255, 0, 0),  # Blue
        thickness=4,
        tip_length=0.2,
    )

    if left_line_buffer:
        left_poly_avg = np.mean(left_line_buffer, axis=0)
        draw_poly_line(
            bird_view,
            left_poly_avg,
            top_y,
            bottom_y,
            color=(255, 0, 0),
            thickness=5,
            alpha=0.5,
        )

    if right_line_buffer:
        right_poly_avg = np.mean(right_line_buffer, axis=0)
        draw_poly_line(
            bird_view,
            right_poly_avg,
            top_y,
            bottom_y,
            color=(0, 0, 255),
            thickness=5,
            alpha=0.5,
        )

    # Draw semi-transparent green overlay
    if detected_left_line and detected_right_line:
        overlay = bird_view.copy()
        pts = np.array(
            [
                [np.polyval(left_poly_avg, bottom_y), bottom_y],
                [np.polyval(left_poly_avg, top_y), top_y],
                [np.polyval(right_poly_avg, top_y), top_y],
                [np.polyval(right_poly_avg, bottom_y), bottom_y],
            ],
            np.int32,
        )
        pts = pts.reshape((-1, 1, 2))
        cv2.fillPoly(overlay, [pts], (0, 255, 0))
        cv2.addWeighted(overlay, 0.4, bird_view, 0.6, 0, bird_view)

    # Average the position of the left and right lanes if detected
    if detected_left_line and detected_right_line:
        # Calculate average lines using polynomial fit
        left_poly = np.polyfit(left_line_y, left_line_x, deg=1)
        right_poly = np.polyfit(right_line_y, right_line_x, deg=1)

        # Calculate the x positions of each lane at the top and bottom y coordinates
        left_bottom_x = np.polyval(left_poly, bottom_y)
        left_top_x = np.polyval(left_poly, top_y)
        right_bottom_x = np.polyval(right_poly, bottom_y)
        right_top_x = np.polyval(right_poly, top_y)

        # Calculate the midpoints of the top and bottom positions
        bottom_midpoint_x = (left_bottom_x + right_bottom_x) / 2
        top_midpoint_x = (left_top_x + right_top_x) / 2

        # Draw the dynamic center line
        cv2.line(
            bird_view,
            (int(bottom_midpoint_x), bottom_y),
            (int(top_midpoint_x), top_y),
            (0, 255, 255),
            2,
        )
        if int(top_midpoint_x) == int(bottom_midpoint_x):
            steering_angle = 90
        else:
            center_line_slope = (top_y - bottom_y) / (
                int(top_midpoint_x) - int(bottom_midpoint_x)
            )
            steering_angle = math.atan(abs(center_line_slope)) * 180 / math.pi
            if center_line_slope > 0:
                steering_angle -= 180
                steering_angle = abs(steering_angle)
        cv2.putText(
            img,
            f"Required Steering Angle: {int(steering_angle)}",
            (10, 25),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.5,
            (255, 255, 255),
            2,
            cv2.LINE_AA,
        )
        if steering_angle >= 135:
            steering_angle = 135
        elif steering_angle <= 45:
            steering_angle = 45
        if abs(steering_angle - int(angle_buffer)) >= 5:
            # client.publish("esp/subtopic", str(int(steering_angle)))
            angle_buffer = steering_angle
    else:
        # Optionally handle cases where one or neither lane is detected
        pass

    # Update text to indicate direction of deviation
    cv2.putText(
        img,
        f"{abs_deviation_meters:.2f} m {deviation_direction} of center",
        (10, 65),
        cv2.FONT_HERSHEY_SIMPLEX,
        0.5,
        (255, 255, 255),
        2,
        cv2.LINE_AA,
    )
    return get_hconcat_frames(img, bird_view)

def draw_poly_line(
    img, poly, top_y, bottom_y, color=(255, 0, 0), thickness=5, alpha=0.5
):
    """
    Draws a semi-transparent line on the image based on polynomial coefficients, extending from bottom_y to top_y.

    Parameters:
    - img: Original image.
    - poly: Polynomial coefficients for the line equation.
    - top_y: Top Y-coordinate for the line.
    - bottom_y: Bottom Y-coordinate for the line.
    - color: Line color.
    - thickness: Line thickness.
    - alpha: Transparency of the line.
    """
    # Create an overlay for drawing lines
    lines_overlay = img.copy()

    x_start = int(np.polyval(poly, bottom_y))
    x_end = int(np.polyval(poly, top_y))

    # Draw the line on the overlay
    cv2.line(lines_overlay, (x_start, bottom_y), (x_end, top_y), color, thickness)

    # Blend the overlay with the original image
    cv2.addWeighted(lines_overlay, alpha, img, 1 - alpha, 0, img)

