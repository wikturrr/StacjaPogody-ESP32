import paho.mqtt.client as mqtt
import os
from dotenv import load_dotenv
from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

load_dotenv()

INFLUX_TOKEN = os.getenv('INFLUX_TOKEN')
INFLUX_ORG = os.getenv('INFLUX_ORG')
INFLUX_BUCKET = os.getenv('INFLUX_BUCKET')
BROKER_IP = os.getenv('BROKER_IP')

def on_connect(client,userdata,flags,rc):
    print(f"Polaczono sie z brokerem {rc}")
    client.subscribe("stacja/#")

def on_message(client,userdata,msg):
    wartosc = float(msg.payload.decode("utf-8"))
    temat = msg.topic
    print(f"Nowy odczyt: {msg.topic}, value {wartosc}")

    point = Point("Pomiary").tag("czujnik", temat).field("wartosc", wartosc)

    write_api.write(bucket=INFLUX_BUCKET, record=point)
    print(f"Zapisano {temat} = {wartosc}")

client_db = InfluxDBClient(url="http://localhost:8086", token=INFLUX_TOKEN, org=INFLUX_ORG)
write_api = client_db.write_api(write_options=SYNCHRONOUS)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

broker_ip = os.getenv('BROKER_IP')

print(f"Proba poloczenia {broker_ip}")
client.connect(broker_ip, 1883, 60)

client.loop_forever()