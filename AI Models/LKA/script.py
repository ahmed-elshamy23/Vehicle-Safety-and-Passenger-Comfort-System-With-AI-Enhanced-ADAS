
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
    # Convert the image to grayscale
    frame = cv2.cvtColor(captured, cv2.COLOR_BGR2HSV)
    frame = cv2.GaussianBlur(frame, (5, 5), 0)
    edges = cv2.Canny(frame, 75, 150)
    edges = region(edges)
    lines = cv2.HoughLinesP(edges, 1, np.pi/180, threshold=30, maxLineGap=150)
    result_image = display_lines(captured, lines)
    showResults(captured, result_image)