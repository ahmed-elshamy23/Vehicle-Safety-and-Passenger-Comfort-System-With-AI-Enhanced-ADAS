import cv2
import numpy as np
import datetime
from lka_modules.pid import PIDController
import datetime
import matplotlib.pyplot as plt
import math
import paho.mqtt.client as mqtt

from time import sleep  # import function sleep for delay
from lka_modules.global_variables import *
from lka_modules.trackbars import *
from lka_modules.image_processing import *
from lka_modules.drawer import *  # it also includes detectors
from lka_modules.fileIO import *

# ONLY FOR LINUX ENVIRONMENT
import os

os.environ["QT_QPA_PLATFORM"] = "xcb"


# Video Processing
def main(video_path):
    """
    Processes the video for lane detection.

    Parameters:
    - video_path: Path to the video file.
    """
    if VIDEO_OR_CAMERA == "video":
        video_capture = cv2.VideoCapture(video_path)
    else:
        video_capture = cv2.VideoCapture(camera_ip)
    if not video_capture.isOpened():
        raise IOError(f"Cannot open video {video_path}")

    # Create a window with trackbars for adjusting the region of interest
    create_trackbar_window("result")

    # Create a file to store the offsets
    unique_filename = (
        datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S") + "_offsets.txt"
    )
    offset_file = open(unique_filename, "w")

    # Create a file to store the control actions
    control_actions_filename = unique_filename.replace(
        "_offsets.txt", "_control_actions.txt"
    )
    control_actions_file = open(control_actions_filename, "w")

    while True:
        ret, frame = video_capture.read()
        (
            horizon,
            bottom,
            left_margin,
            right_margin,
            top_left_margin,
            top_right_margin,
        ) = get_trackbar_values("result")
        meta_data = {
            "HORIZON": horizon,
            "BOTTOM_TRIM": bottom,
            "LEFT_MARGIN": left_margin,
            "RIGHT_MARGIN": right_margin,
            "TOP_LEFT_MARGIN": top_left_margin,
            "TOP_RIGHT_MARGIN": top_right_margin,
            "KP": pid_controller.kp,
            "KI": pid_controller.ki,
            "KD": pid_controller.kd,
        }
        if not ret:
            print("Reached the end of the video.")
            print(meta_data)
            break

        height, width = frame.shape[:2]
        top_y = int(height * horizon / 100.0)
        bottom_y = int(height * bottom / 100.0)

        vertices = np.array(
            [
                [
                    (
                        width * left_margin / 100.0,
                        height * bottom / 100.0,
                    ),  # Bottom left
                    (
                        width * top_left_margin / 100.0,
                        height * horizon / 100.0,
                    ),  # Top left
                    (
                        width * top_right_margin / 100.0,
                        height * horizon / 100.0,
                    ),  # Top right
                    (
                        width * right_margin / 100.0,
                        height * bottom / 100.0,
                    ),  # Bottom right
                ]
            ],
            dtype=np.int32,
        )

        bird_view = bird_eye_view(vertices, frame)

        canny_image = canny_edge_detector(bird_view)
        # cropped_canny = region_of_interest(canny_image, vertices)
        # lines = detect_lines(cropped_canny)
        lines = detect_lines(canny_image)
        combo_image = draw_lines(
            frame, bird_view, lines, top_y, bottom_y, offset_file, control_actions_file
        )

        # Draw the ROI only if HIDE_ROI is False
        if not HIDE_ROI:
            combo_image = draw_roi(combo_image, vertices)

        # cv2.imshow("canny", canny_image)
        # concated = get_hconcat_frames(combo_image, canny_image)
        cv2.imshow("result", cv2.resize(combo_image, (0, 0), fx=0.5, fy=0.5))
        if cv2.waitKey(1) & 0xFF == ord("q"):
            print("Exiting...")
            print("File saved as:", unique_filename)

            print(f"meta data: {meta_data}")

            break

    # Clean up
    video_capture.release()
    cv2.destroyAllWindows()
    offset_file.close()
    control_actions_file.close()

    # Read the deviation and control actions data
    deviation_data = read_data_from_file(unique_filename)
    control_actions_data = read_data_from_file(control_actions_filename)

    fig, ax1 = plt.subplots()
    ax1.set_xlabel("Frames")
    ax1.set_ylabel("Deviation from Center (m)", color="tab:red")
    ax1.plot(deviation_data, color="tab:red", label="Deviation")
    ax1.tick_params(axis="y", labelcolor="tab:red")

    ax2 = ax1.twinx()  # instantiate a second axes that shares the same x-axis
    ax2.set_ylabel("Control Action", color="tab:blue")
    ax2.plot(control_actions_data, color="tab:blue", label="Control Action")
    ax2.tick_params(axis="y", labelcolor="tab:blue")

    fig.tight_layout()  # otherwise the right y-label is slightly clipped
    plt.title("Deviation and Control Action Over Time")
    plt.show()

    # Plotting the deviation from center
    plt.figure(figsize=(10, 5))
    plt.plot(deviation_data, label="Deviation from Center")
    plt.axhline(0, color="r", linestyle="--")
    plt.xlabel("Frames")
    plt.ylabel("Deviation (meters)")
    plt.title("Deviation from Lane Center Over Time")
    plt.legend()
    plt.show()

    # Plotting the control actions
    plt.figure(figsize=(10, 5))
    plt.plot(control_actions_data, label="Control Action")
    plt.xlabel("Frames")
    plt.ylabel("Control Action Value")
    plt.title("PID Control Actions Over Time")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    video_paths = [
        "test_videos/test1.mp4",  # 0
        "test_videos/test2.mp4",  # 1
        "test_videos/test3.mp4",  # 2
        "test_videos/test4.mp4",  # 3
        "test_videos/test5.mp4",  # 4
        "test_videos/test6.mp4",  # 5
        "test_videos/test7.mp4",  # 6
    ]
    try:
        main(video_paths[2])
    except Exception as e:
        print(f"Error processing video: {e}")
