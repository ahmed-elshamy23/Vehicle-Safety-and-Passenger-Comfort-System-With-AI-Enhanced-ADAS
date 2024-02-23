import cv2
import numpy as np

class LaneDetector:
    def __init__(self, lower_yellow, upper_yellow, roi_parm):
        self.lower_yellow = lower_yellow
        self.upper_yellow = upper_yellow
        self.roi_parm = roi_parm

    def ROI(self, image):
        height, width = image.shape[0], image.shape[1]

        left, center, right = self.roi_parm
        
        triangle = np.array([
            [(int(width*left), height), (int(width*0.5), int(height*center)), (int(width*right), height)]
        ])

        mask = np.zeros_like(image)

        cv2.fillPoly(mask, triangle, (255,255,255))

        masked_image = cv2.bitwise_and(image, mask)
        return masked_image


    def average_lines(self, lines):
        if lines is None:
            return None

        right_lines = []
        left_lines = []

        for line in lines:
            x1, y1, x2, y2 = line[0]

            try:
                slope = (y2 - y1) / (x2 - x1)
            except ZeroDivisionError:
                continue

            if slope > 0:
                right_lines.append(line)
            elif slope < 0:
                left_lines.append(line)

        # Calculate average lines
        avg_right_line = self.calculate_average_line(right_lines)
        avg_left_line = self.calculate_average_line(left_lines)

        return avg_right_line, avg_left_line

    def calculate_average_line(self, lines):
        if not lines:
            return None

        x1_avg = int(np.mean([line[0][0] for line in lines]))
        y1_avg = int(np.mean([line[0][1] for line in lines]))
        x2_avg = int(np.mean([line[0][2] for line in lines]))
        y2_avg = int(np.mean([line[0][3] for line in lines]))

        return [(x1_avg, y1_avg, x2_avg, y2_avg)]



    def detect_lanes(self, image, blur_kernel=(5, 5), canny_params=(50, 150)):
        blurred = cv2.GaussianBlur(image, blur_kernel, 3)
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
        gray = cv2.cvtColor(blurred, cv2.COLOR_BGR2GRAY)

        mask_yellow = cv2.inRange(hsv, self.lower_yellow, self.upper_yellow)
        mask_white = cv2.inRange(gray, 200, 255)
        mask_yw = cv2.bitwise_or(mask_white, mask_yellow)
        mask_yw_image = cv2.bitwise_and(hsv, hsv, mask_yw)

        edges = cv2.Canny(mask_yw_image, *canny_params)
        
        mask = np.zeros(edges.shape[:2], np.uint8)
        mask[edges.shape[0] // 2:, :] = 255
        edges = cv2.bitwise_and(edges, mask)

        roi = self.ROI(edges)
        lines = cv2.HoughLinesP(roi, 2, np.pi/180, threshold=50, maxLineGap=100)

        return self.average_lines(lines)
    

class LaneDetectorResult:
    def __init__(self, image, lines):
        self.image = image
        self.lines = lines

    def calculate_error(self):
        if self.lines is not None:
            lane_center_x = np.mean([np.mean([line[0][0], line[0][2]]) for line in self.lines])
            scene_center_x = self.image.shape[1] // 2
            error = lane_center_x - scene_center_x
            return error
        else:
            return None

    def plot_lanes_and_center_line(self):
        if self.lines is not None:
            lane_image = np.zeros_like(self.image)
            for line in self.lines:
                x1, y1, x2, y2 = line[0]
                cv2.line(lane_image, (x1, y1), (x2, y2), (0, 255, 0), thickness=5)
            self.image = cv2.addWeighted(self.image, 1, lane_image, 0.4, 0)
        
        # Calculate average x-coordinate of detected lines
        if self.lines:
            lane_center_x = np.mean([np.mean([line[0][0], line[0][2]]) for line in self.lines])
        else:
            lane_center_x = self.image.shape[1] // 2

        # Draw center line
        height, width = self.image.shape[0], self.image.shape[1]
        center_x = int(lane_center_x)
        cv2.line(self.image, (center_x, 0), (center_x, height), (0, 0, 255), thickness=3)

        # Display error
        error = self.calculate_error()
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(self.image, f"Error: {error}", (50, 50), font, 1, (255, 0, 0), 2, cv2.LINE_AA)

        return self.image

