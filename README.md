# 🩺 Smart Health Monitoring System (IoT Based)

An **IoT-based Smart Health Monitoring System** designed to continuously monitor vital health parameters and transmit the data remotely using the internet.
The system measures **ECG signals, body temperature, blood oxygen (SpO₂), heart rate (BPM), eye blink detection, and body movement** and sends the data to a **Telegram bot for real-time monitoring**.

This project is useful for **remote patient monitoring, elderly care, and emergency health tracking**.

---

# 📌 Project Overview

This system collects health data from multiple biomedical sensors connected to a microcontroller system consisting of **Arduino UNO and ESP32**.

The collected data is:

1. Displayed locally on an **LCD display**
2. Sent to a **Telegram Bot** via WiFi
3. Used to monitor patient health in **real time**

If abnormal values are detected, the system can notify the user instantly.

---

# 📷 Project Images

### System Prototype

![Image](https://iotdesignpro.com/sites/default/files/main-image/IoT-Based-Remote-Patient%20-Monitoring-System.jpg)

![Image](https://circuitdigest.com/sites/default/files/projectimage_mic/IoT-based-Patient-Monitoring-System-using-ESP8266-and-Arduino.jpg)

![Image](https://github.com/Arnav123121/Smart-Health-Monitoring-System/blob/main/System%20(5).jpeg?raw=true)

![Image](https://github.com/Arnav123121/Smart-Health-Monitoring-System/blob/main/System%20(6).jpeg?raw=true)

![Image](https://github.com/Arnav123121/Smart-Health-Monitoring-System/blob/main/System%20(4).jpeg?raw=true)

### Telegram Bot Monitoring

![Image](https://github.com/Arnav123121/Smart-Health-Monitoring-System/blob/main/Telegram%20(1).jpeg?raw=true)

![Image](https://github.com/Arnav123121/Smart-Health-Monitoring-System/blob/main/Telegram%20(2).jpeg?raw=true)
---

# ⚙️ Features

✔ Real-time **ECG signal monitoring**
✔ **Heart rate (BPM)** measurement
✔ **Blood Oxygen (SpO₂)** monitoring
✔ **Body temperature** measurement
✔ **Eye blink detection** for fatigue monitoring
✔ **Motion detection** using accelerometer
✔ Data displayed on **LCD screen**
✔ **Telegram bot integration** for remote monitoring
✔ **IoT based health alerts**

---

# 🧠 System Architecture

```
Sensors
   ↓
Arduino UNO (Sensor Processing)
   ↓
ESP32 (WiFi Communication)
   ↓
Telegram Bot
   ↓
User Smartphone
```

---

# 🧩 Hardware Components

| Component                 | Purpose                            |
| ------------------------- | ---------------------------------- |
| ESP32 WROOM 32            | WiFi communication                 |
| Arduino UNO               | Sensor data processing             |
| MAX30100                  | Heart rate & SpO₂ sensor           |
| AD8232 ECG Sensor         | ECG signal monitoring              |
| DS18B20                   | Body temperature sensor            |
| ADXL345                   | Accelerometer for motion detection |
| IR Blink Sensor           | Eye blink detection                |
| 16x2 LCD Display          | Local health parameter display     |
| ECG Electrodes            | ECG signal acquisition             |
| Breadboard & Jumper Wires | Circuit connections                |
| Power Supply              | System power                       |

---

# 🧪 Parameters Monitored

| Parameter           | Sensor Used     |
| ------------------- | --------------- |
| Heart Rate (BPM)    | MAX30100        |
| Blood Oxygen (SpO₂) | MAX30100        |
| ECG Signal          | AD8232          |
| Body Temperature    | DS18B20         |
| Eye Blink Detection | IR Blink Sensor |
| Body Motion         | ADXL345         |

---

# 🌐 IoT Integration

The system uses **ESP32 WiFi connectivity** to send health data to a **Telegram Bot**.

The bot sends periodic messages containing:

```
Health Parameters

Temperature: XX °C
ECG Value: XXX
Blink Status: YES / NO
Heart Rate (BPM): XX
SpO2 Level: XX %
AX: X.XX
AY: X.XX
AZ: X.XX
```

Users can monitor the patient remotely through their smartphone.

---

# 🔌 Circuit Connections (Example)

### MAX30100 → ESP32

```
VIN → 3.3V
GND → GND
SCL → GPIO22
SDA → GPIO21
```

### AD8232 ECG Sensor

```
OUTPUT → Analog Pin
LO+ → Digital Pin
LO- → Digital Pin
```

### DS18B20

```
DATA → Digital Pin
VCC → 5V
GND → GND
```

---

# 💻 Software Requirements

* Arduino IDE
* ESP32 Board Package
* Required Libraries:

```
WiFi.h
Wire.h
MAX30100_PulseOximeter.h
DallasTemperature.h
OneWire.h
Adafruit_ADXL345.h
UniversalTelegramBot.h
LiquidCrystal_I2C.h
```

---

# 🚀 How to Run the Project

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/yourusername/smart-health-monitoring-system.git
```

---

### 2️⃣ Install Libraries

Install all required libraries from **Arduino Library Manager**.

---

### 3️⃣ Configure WiFi & Telegram Bot

Update these values in the code:

```
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
#define BOT_TOKEN "YOUR_TELEGRAM_BOT_TOKEN"
```

---

### 4️⃣ Upload Code

Upload the code to:

* Arduino UNO
* ESP32

---

### 5️⃣ Start Monitoring

Open Telegram and start the bot:

```
@Smart_Health_Monitor_bot
```

You will start receiving health data.

---

# 📊 Applications

* Remote Patient Monitoring
* Elderly Health Care
* Hospital Patient Tracking
* Emergency Health Alert Systems
* Wearable Health Devices

---

# 🔮 Future Improvements

* Mobile App integration
* Cloud database storage
* AI based health prediction
* Real time ECG graph visualization
* GPS based patient location tracking

---

# 👨‍💻 Author

**Arnav Domalwar**

Electronics & IoT Developer

---

# ⭐ Contribute

Contributions are welcome!

Just tell me 👍
