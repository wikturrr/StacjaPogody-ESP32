import paho.mqtt.client as mqtt
import os
from dotenv import load_dotenv

load_dotenv()

def on_connect(client,userdata,flags,rc):
    print(f"Polaczono sie z brokerem {rc}")
    client.subscribe("stacja/#")

def on_message(client,userdata,msg):
    wartosc = msg.payload.decode("utf-8")
    print(f"Nowy odczyt: {msg.topic}, value {wartosc}")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

broker_ip = os.getenv('BROKER_IP')

print(f"Proba poloczenia {broker_ip}")
client.connect(broker_ip, 1883, 60)

client.loop_forever()