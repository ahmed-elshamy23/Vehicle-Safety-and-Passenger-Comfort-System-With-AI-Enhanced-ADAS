import cv2
import numpy as np
from LKA_module import LaneDetector, LaneDetectorResult

cap = cv2.VideoCapture('inVideosExamples/harder_challenge_video.mp4')

ret, frame = cap.read()
if not ret:
    print("Error reading video")
    exit()

lower_yellow = np.array([0, 0, 0])
upper_yellow = np.array([30, 255, 255])
roi_parm = (0, 0.3, 1)

detector = LaneDetector(lower_yellow, upper_yellow, roi_parm)
lane_result = LaneDetectorResult(frame, None)

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break  # Break the loop if the video ends

    lines = detector.detect_lanes(frame)
    lane_result.image = frame
    lane_result.lines = lines

    result_frame = lane_result.plot_lanes_and_center_line()

    cv2.imshow('Lane Detection', result_frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

