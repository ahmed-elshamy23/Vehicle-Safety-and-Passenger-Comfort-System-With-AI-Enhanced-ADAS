from face_reco import *


def calculate_EAR(point):
    A = distance.euclidean(point[1], point[5])
    B = distance.euclidean(point[2], point[4])
    C = distance.euclidean(point[0], point[3])
    EAR = (A + B) / (2.0 * C)
    return EAR


mp_face_mesh = mp.solutions.face_mesh
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles

chosen_left_eye_idxs = [362, 385, 387, 263, 373, 380]
chosen_right_eye_idxs = [33, 160, 158, 133, 153, 144]

# Coordinates storage for left and right eye points
left_eye_coordinates = []
right_eye_coordinates = []

# Initialize Pygame and load the alarm sound
pygame.init()
alarm_sound = pygame.mixer.Sound("warn.wav")
alarm_start_time = None
alarm_duration = 5  # Duration of the alarm in seconds

webcam = cv2.VideoCapture(0)

# Initialize MQTT client
mqtt_client = mqtt.Client()

# Define MQTT broker and topic
mqtt_broker = "localhost"
mqtt_topic = "esp/subtopic"


def send_mqtt_message(message):
    mqtt_client.connect(mqtt_broker)
    mqtt_client.publish(mqtt_topic, message)
    mqtt_client.disconnect()


while webcam.isOpened():
    success, img = webcam.read()

    # Applying face mesh model
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = mp_face_mesh.FaceMesh(refine_landmarks=True).process(img)

    # Draw annotations
    img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
    if results.multi_face_landmarks:
        for face_landmarks in results.multi_face_landmarks:
            left_eye_coordinates.clear()
            right_eye_coordinates.clear()

            for idx in chosen_left_eye_idxs:
                point = face_landmarks.landmark[idx]
                x = int(point.x * img.shape[1])
                y = int(point.y * img.shape[0])
                cv2.circle(img, (x, y), 2, (0, 255, 0), -1)
                left_eye_coordinates.append((x, y))

            for idx in chosen_right_eye_idxs:
                point = face_landmarks.landmark[idx]
                x = int(point.x * img.shape[1])
                y = int(point.y * img.shape[0])
                cv2.circle(img, (x, y), 2, (0, 255, 0), -1)
                right_eye_coordinates.append((x, y))

            # Print coordinates of chosen points around each eye
            print("Coordinates of Chosen Points around Left Eye:")
            for idx, (x, y) in zip(chosen_left_eye_idxs, left_eye_coordinates):
                print(f"Point {idx}: X={x}, Y={y}")
            print("\nCoordinates of Chosen Points around Right Eye:")
            for idx, (x, y) in zip(chosen_right_eye_idxs, right_eye_coordinates):
                print(f"Point {idx}: X={x}, Y={y}")

            mp_drawing.draw_landmarks(
                image=img,
                landmark_list=face_landmarks,
                connections=mp_face_mesh.FACEMESH_IRISES,
                landmark_drawing_spec=None,
                connection_drawing_spec=mp_drawing_styles.get_default_face_mesh_iris_connections_style(),
            )
            mp_drawing.draw_landmarks(
                image=img,
                landmark_list=face_landmarks,
                connections=mp_face_mesh.FACEMESH_TESSELATION,
                landmark_drawing_spec=None,
                connection_drawing_spec=mp_drawing_styles.get_default_face_mesh_tesselation_style(),
            )
            mp_drawing.draw_landmarks(
                image=img,
                landmark_list=face_landmarks,
                connections=mp_face_mesh.FACEMESH_CONTOURS,
                landmark_drawing_spec=None,
                connection_drawing_spec=mp_drawing_styles.get_default_face_mesh_contours_style(),
            )

            # Draw chosen points around the eyelid for both eyes
            for x, y in left_eye_coordinates:
                cv2.circle(img, (x, y), 2, (0, 255, 0), -1)

            for x, y in right_eye_coordinates:
                cv2.circle(img, (x, y), 2, (0, 255, 0), -1)

            # Calculate EAR and print it for both eyes
            EAR_left = calculate_EAR(left_eye_coordinates)
            EAR_right = calculate_EAR(right_eye_coordinates)
            # Calculate average EAR
            average_ear = (EAR_left + EAR_right) / 2

            print("EAR Left:", EAR_left)
            print("EAR Right:", EAR_right)
            print("EAR Average:", average_ear)

            # Check if alarm conditions are met
            if average_ear > 0.45 or average_ear < 0.15:
                if alarm_start_time is None:
                    alarm_start_time = time.time()
                elif (
                    time.time() - alarm_start_time >= 4
                ):  # Check if condition has persisted for 4 seconds
                    # Play alarm for 5 seconds
                    alarm_sound.play()
                    print("Alarm triggered!")
                    cv2.imshow("Koolac", img)
                    cv2.waitKey(5000)  # Wait for 5 seconds
                    alarm_start_time = None  # Reset alarm start time
                    # Send MQTT message
                    send_mqtt_message("139")

    else:
        alarm_start_time = None  # Reset alarm start time if no face is detected

    cv2.imshow("Koolac", img)
    if cv2.waitKey(20) & 0xFF == ord("q"):
        break

webcam.release()
cv2.destroyAllWindows()
