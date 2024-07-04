import cv2
from lka_modules.global_variables import *

def create_trackbar_window(window_name):
    cv2.namedWindow(window_name)
    cv2.createTrackbar("Horizon", window_name, HORIZON, 100, lambda x: None)
    cv2.createTrackbar("Bottom", window_name, BOTTOM_TRIM, 100, lambda x: None)
    cv2.createTrackbar("Bottom Margin", window_name, BOTTOM_MARGIN, 100, lambda x: None)
    cv2.createTrackbar(
        "Top Margin", window_name, TOP_MARGIN, 100, lambda x: None
    )
    cv2.createTrackbar("KP", window_name, KP, 100, lambda x: None)
    cv2.createTrackbar("KI", window_name, KI, 100, lambda x: None)
    cv2.createTrackbar("KD", window_name, KD, 100, lambda x: None)


def get_trackbar_values(window_name):
    horizon = cv2.getTrackbarPos("Horizon", window_name)
    bottom = cv2.getTrackbarPos("Bottom", window_name)
    left_margin = cv2.getTrackbarPos("Bottom Margin", window_name)
    top_left_margin = cv2.getTrackbarPos("Top Margin", window_name)
    right_margin = 100 - left_margin
    top_right_margin = 100 - top_left_margin
    
    pid_controller.kp = cv2.getTrackbarPos("KP", window_name) / 100
    pid_controller.ki = cv2.getTrackbarPos("KI", window_name) / 100
    pid_controller.kd = cv2.getTrackbarPos("KD", window_name) / 100
    return horizon, bottom, left_margin, right_margin, top_left_margin, top_right_margin
