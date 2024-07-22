import time
import paho.mqtt.client as paho
import ssl

def on_message(client, userdata, message):
    print("Received message: ", str(message.payload.decode("utf-8")))

client = paho.Client()
client.on_message = on_message

client.tls_set(ca_certs="certs/mqtt_server.crt", certfile="certs/mqtt_server.crt",  keyfile="certs/mqtt_server.key", keyfile_password="1234",  tls_version=ssl.PROTOCOL_TLSv1_2)
client.tls_insecure_set(True)

client.connect("192.168.1.12", 1883)

x = 1

##start loop to process received messages
client.loop_start()
while(1):
    client.publish(f"x = {x}")
    x += 1
    time.sleep(5)
