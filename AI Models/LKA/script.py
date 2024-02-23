
import cv2
import matplotlib.pyplot as plt
import numpy as np

def region(image):
    height, width = image.shape[0], image.shape[1]
    triangle = np.array([
                       [(100, height), (475, 300), (width, height)]
                       ])
    mask = np.zeros_like(image)
    mask = cv2.fillPoly(mask, triangle, 255)
    mask = cv2.bitwise_and(image, mask)
    return mask

def display_lines(image, lines):
    lines_image = np.copy(image)  # Create a copy of the original image
    if lines is not None:
        for line in lines:
            x1, y1, x2, y2 = line[0]  # Extract line coordinates
            cv2.line(lines_image, (x1, y1), (x2, y2), (0, 255, 0), 1)  # Draw the line in red (0, 0, 255)
    return lines_image


def showResults(original, detected):
    plt.figure(figsize=(12, 5))
    # Plot the original image in the first subplot
    plt.subplot(1, 2, 1)
    plt.imshow(cv2.cvtColor(original, cv2.COLOR_BGR2RGB))
    plt.title("Original Image")
    plt.axis('off')  

    plt.subplot(1, 2, 2)
    plt.imshow(cv2.cvtColor(detected, cv2.COLOR_BGR2RGB)) 
    plt.title("Detected Lanes")
    plt.axis('off')  

    plt.show()


def laneDetect(captured):
    plt.subplot(2, 2, 1)
    plt.imshow(captured)
    plt.title("Captured Lanes")
    plt.axis('off')

    gausian = cv2.GaussianBlur(captured, (5, 5), 3)
    hsv = cv2.cvtColor(gausian, cv2.COLOR_BGR2HSV)
    gray = cv2.cvtColor(gausian, cv2.COLOR_BGR2GRAY)

    plt.subplot(2, 2, 2)
    plt.imshow(hsv)
    plt.title("HSV Lanes")
    plt.axis('off')

    lower_yellow = np.array([20, 100, 100])
    upper_yellow = np.array([30, 255, 255])
    mask_yellow = cv2.inRange(hsv, lower_yellow, upper_yellow)
    mask_white = cv2.inRange(gray, 200, 255)
    mask_yw = cv2.bitwise_or(mask_white, mask_yellow)
    mask_yw_image = cv2.bitwise_and(gray, mask_yw)
        
    edges = cv2.Canny(mask_yw_image, 75, 150)
    mask = np.zeros(edges.shape[:2], np.uint8)
    mask[edges.shape[0] // 2:, :] = 255
    edges = cv2.bitwise_and(edges, mask)

    plt.subplot(2, 2, 3)
    plt.imshow(mask_yw_image)
    plt.title("Canny Lanes")
    plt.axis('off')



    lines = cv2.HoughLinesP(edges, 2, np.pi/180, threshold= 50, maxLineGap=150)

    result_image = display_lines(captured, lines)
    plt.subplot(2, 2, 4)
    plt.imshow(result_image
    )
    plt.title("Result Images")
    plt.axis('off')

    plt.show()
