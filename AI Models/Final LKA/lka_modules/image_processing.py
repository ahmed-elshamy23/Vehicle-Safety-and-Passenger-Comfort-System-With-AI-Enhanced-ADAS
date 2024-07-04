import cv2
import numpy as np
from lka_modules.global_variables import *

def canny_edge_detector(img):
    """
    Applies Canny edge detection algorithm to the input image after converting it to HSL color space.

    Parameters:
    - img: Input image in BGR format.

    Returns:
    - Edge-detected image.
    """
    if img is None:
        raise ValueError("Input image is None.")

    # Convert the image to HSL color space
    hsl = cv2.cvtColor(img, cv2.COLOR_BGR2HLS)

    # Use the Lightness channel.
    lightness = hsl[:, :, 1]

    median_intensity = np.median(lightness)
    lower_threshold = int(max(0, (1.0 - 0.33) * median_intensity))
    upper_threshold = int(min(255, (1.0 + 0.33) * median_intensity))

    # Apply gaussian blur to reduce noise
    blur = cv2.GaussianBlur(lightness, (5, 5), 0)
    edges = cv2.Canny(blur, lower_threshold, upper_threshold)

    return edges


def region_of_interest(edges, vertices):
    """
    Applies a mask to the input edge-detected image to focus on the region of interest based on the vertices calculated from global variables or trackbar values.

    Parameters:
    - edges: Edge-detected image.
    - vertices: Vertices of the polygon to mask the image.

    Returns:
    - Masked edge-detected image focusing on the region of interest.
    """
    mask = np.zeros_like(edges)

    # Assuming that vertices are in the correct format, fill the polygon
    cv2.fillPoly(mask, [vertices], 255)

    # Apply the mask to the edge-detected image
    masked_edges = cv2.bitwise_and(edges, mask)

    # cv2.imshow("roi", masked_edges)
    # cv2.waitKey(0)

    return masked_edges

def bird_eye_view(ROI, frame):
    bottom_left =    ROI[0][0]
    top_left =       ROI[0][1]
    top_right =      ROI[0][2]
    bottom_right =   ROI[0][3]

    height, width = frame.shape[:2]
    src_vert = np.float32([bottom_left, bottom_right, top_right, top_left])
    dest_vert = np.float32([[0, height], [width, height], [width, 0], [0, 0]])
    
    matrix = cv2.getPerspectiveTransform(src_vert, dest_vert)
    return cv2.warpPerspective(frame, matrix, (width, height))
