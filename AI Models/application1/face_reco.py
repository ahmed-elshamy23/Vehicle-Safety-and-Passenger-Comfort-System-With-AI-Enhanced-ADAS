from libraries import *

# MQTT Broker
broker_address = "mqtt.eclipseprojects.io"
port = 1883
# Create a MQTT client
client = mqtt.Client("FaceRecognitionClient")
client.connect(broker_address, port)


path = "Known"
className = []
images = []
personlist = os.listdir(path)
# print(personlist)

for person in personlist:
    current_person = cv2.imread(f"{path}/{person}")
    images.append(current_person)
    className.append(os.path.splitext(person)[0])

print(className)


def image_Encodeing(img):
    encodelist = []
    for im in img:
        im = cv2.cvtColor(im, cv2.COLOR_BGR2RGB)
        encode = face_recognition.face_encodings(im)[0]
        encodelist.append(encode)
    return encodelist


encodelistknown = image_Encodeing(images)
print("Encodeing complete\n")

cap = cv2.VideoCapture(0)
_, img = cap.read()

imgs = cv2.resize(img, (0, 0), None, 0.25, 0.25)
imgs = cv2.cvtColor(imgs, cv2.COLOR_BGR2RGB)

faceCurrentFram = face_recognition.face_locations(imgs)
encodeCurrnetFrame = face_recognition.face_encodings(imgs, faceCurrentFram)

for encodeface, faceloc in zip(encodeCurrnetFrame, faceCurrentFram):
    matches = face_recognition.compare_faces(encodelistknown, encodeface)
    faceDis = face_recognition.face_distance(encodelistknown, encodeface)
    matchIndex = np.argmin(faceDis)

    if matches[matchIndex]:
        name = className[matchIndex]
        print(name)
        y1, x2, y2, x1 = faceloc
        y1, x2, y2, x1 = y1 * 4, x2 * 4, y2 * 4, x1 * 4
        cv2.rectangle(img, (x1, y1), (x2, y2), (0, 0, 255), 2)
        cv2.rectangle(img, (x1, y2 - 35), (x2, y2), (0, 0, 255), cv2.FILLED)
        cv2.putText(
            img, name, (x1 + 6, y2 - 6), cv2.FONT_HERSHEY_COMPLEX, 1, (255, 255, 255), 2
        )
        # Publish MQTT message based on recognition result
        if name == "Elon":
            client.publish("esp/subtopic", "136")
        elif name == "Mo_salah":
            client.publish("esp/subtopic", "137")
        elif name == "Treka":
            client.publish("esp/subtopic", "138")


cv2.imshow("Face recognition", img)
    if cv2.waitKey(20) & 0xFF == ord('q'):
        break
# Close the video capture
cap.release()
cv2.destroyAllWindows()
