import cv2
import time
import pygame

# Load pre-trained Haar cascade classifier for eye detection from OpenCV
eye_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_eye.xml")

# Initialize webcam
cap = cv2.VideoCapture(0)

# Define a baseline or standard pupil size (you may need to calibrate this based on your specific conditions)
standard_pupil_size = 50  # Adjust this value as needed

# Initialize a timer
start_time = time.time()
alert_duration = 2  # Set the duration threshold for fatigue alert in seconds

# Initialize pygame for playing the alarm sound
pygame.init()
alarm_sound = pygame.mixer.Sound("E:\warn.wav")

while True:
    ret, frame = cap.read()

    # Convert the frame to grayscale for eye detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Detect eyes in the frame
    eyes = eye_cascade.detectMultiScale(gray)

    # Iterate through detected eyes
    for ex, ey, ew, eh in eyes:
        # Calculate pupil size (here, we use the width of the eye bounding box as an approximation)
        pupil_size = ew

        # Compare with the standard pupil size
        if pupil_size < standard_pupil_size:
            status = "Fatigue Detected"
            # Check if the alert duration has exceeded the threshold
            if time.time() - start_time > alert_duration:
                # Play the alarm sound
                pygame.mixer.Sound.play(alarm_sound)

        else:
            status = "normal"
            # Reset the timer if the driver is not fatigued
            start_time = time.time()

        # Display the frame with annotations
        cv2.putText(
            frame,
            f"Pupil Size: {pupil_size}",
            (50, 50),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (0, 255, 0),
            2,
        )
        cv2.putText(
            frame,
            f"Status: {status}",
            (50, 100),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (0, 0, 255),
            2,
        )

    # Display the frame
    cv2.imshow("Frame", frame)

    # Break the loop when 'q' key is pressed
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# Release the webcam and close all windows
cap.release()
cv2.destroyAllWindows()
