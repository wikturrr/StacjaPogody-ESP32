# IoT Weather Station

System monitorowania warunków atmosferycznych w czasie rzeczywistym, integrujący mikrokontroler **ESP32-S** z kontenerową architekturą serwerową. Projekt skupia się na wydajnym przesyłaniu danych pomiarowych oraz ich długoterminowej archiwizacji w celu późniejszej analizy trendów.

---

## Technologie

* **Hardware:** ESP32-S (C++/Arduino), czujnik DHT22.
* **Komunikacja:** MQTT (Broker Mosquitto uruchomiony w Dockerze).
* **Backend:** Python (biblioteki: `paho-mqtt`, `influxdb-client`).
* **Infrastruktura:** Docker Compose (pełna konteneryzacja bazy i brokera).
* **Baza danych:** InfluxDB (Baza danych typu Time-series).

---

## Jak to działa?

1.  **Pomiar:** ESP32-S zbiera dane o temperaturze i wilgotności, a następnie przesyła je bezprzewodowo przez Wi-Fi za pomocą protokołu **MQTT**.
2.  **Broker:** Kontener **Mosquitto** pełni rolę centrum komunikacyjnego, zarządzając ruchem przychodzących wiadomości.
3.  **Przetwarzanie:** Skrypt w **Pythonie** (działający jako subscriber) odbiera dane i natychmiast zapisuje je w bazie **InfluxDB**.
4.  **Analiza:** Dane są archiwizowane i gotowe do wizualizacji bezpośrednio w panelu InfluxDB (**Data Explorer**) lub zewnętrznych narzędziach.

---

## Roadmap

[]Pomiar ciśnienia: Integracja czujnika **BMP280** w celu monitorowania ciśnienia atmosferycznego i precyzyjniejszego prognozowania pogody.
