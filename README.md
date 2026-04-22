IoT Weather Station
System monitorowania warunków atmosferycznych w czasie rzeczywistym, integrujący mikrokontroler ESP32-S z kontenerową architekturą serwerową. Projekt skupia się na wydajnym przesyłaniu danych pomiarowych i ich długoterminowej archiwizacji.

Technologie:
Hardware: ESP32-S (C++/Arduino), czujnik DHT22.
Komunikacja: MQTT (Broker Mosquitto w Dockerze).
Backend: Python (paho-mqtt, influxdb-client).
Infrastruktura: Docker Compose (konteneryzacja bazy i brokera).
Baza danych: InfluxDB (Time-series database).

Jak to działa?
Pomiar: ESP32 zbiera dane o temperaturze i wilgotności, przesyłając je przez Wi-Fi za pomocą protokołu MQTT.
Broker: Kontener Mosquitto zarządza ruchem wiadomości.
Przetwarzanie: Skrypt w Pythonie (subscriber) odbiera dane i w czasie rzeczywistym zapisuje je do bazy InfluxDB.
Analiza: Dane są dostępne do wizualizacji bezpośrednio w panelu InfluxDB (Data Explorer).

Roadmap:
[ ] Rozbudowa o pomiar ciśnienia: Integracja czujnika BMP280/BME280 w celu monitorowania ciśnienia atmosferycznego i precyzyjniejszego prognozowania pogody.
