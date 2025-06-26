# 🏠 Smart Home Automation with Alexa

A complete voice-controlled home automation system using an ESP8266 (NodeMCU) and Amazon Alexa. This project lets you control a light, fan, and door actuator entirely over your local Wi-Fi network—no cloud subscriptions required.

---

## 📋 Table of Contents

1. [Project Overview](#project-overview)  
2. [Components & Tools](#components--tools)  
3. [Circuit Connections](#circuit-connections)  
4. [Software Setup](#software-setup)  
5. [Arduino Code](#arduino-code)  
6. [Alexa Integration](#alexa-integration)  
7. [Testing & Troubleshooting](#testing--troubleshooting)  
8. [Future Enhancements](#future-enhancements)  
9. [License & Support](#license--support)  

---

## Project Overview

This guide walks you through building a **local** smart home system. An ESP8266-based NodeMCU emulates Wemo devices via the `fauxmoESP` library so that any Amazon Echo can discover and control your appliances with simple voice commands:

- “Alexa, turn on light”  
- “Alexa, turn off fan”  
- “Alexa, open door”  

No external servers or subscriptions—everything runs on your LAN.

---

## Components & Tools

| Component               | Qty | Description                                 |
|-------------------------|:---:|---------------------------------------------|
| NodeMCU (ESP8266)       |  1  | Wi-Fi microcontroller board                 |
| 3-Channel Relay Module  |  1  | Switches AC/DC loads (light, fan, door)     |
| Amazon Echo Dot/Show    |  1  | Alexa voice assistant                       |
| Jumper Wires            |  —  | For signal & power connections              |
| USB Cable & Adapter     |  1  | Powers NodeMCU                              |
| Breadboard (optional)   |  1  | Prototyping base                            |
| Computer with Arduino IDE | 1 | Code upload & serial monitor                |

**Libraries / Software**  
- `fauxmoESP` (Wemo emulation)  
- `ESP8266WiFi` (built-in)  
- Arduino Core for ESP8266  

---

## Circuit Connections

1. **Power**  
   - NodeMCU VIN ← USB 5 V supply  
   - NodeMCU GND ↔ Relay Module GND  

2. **Relay Inputs**  
   - Relay IN1 ↔ NodeMCU D1 (GPIO5) → **Light**  
   - Relay IN2 ↔ NodeMCU D2 (GPIO4) → **Fan**  
   - Relay IN3 ↔ NodeMCU D3 (GPIO0) → **Door actuator**  

3. **Relay Outputs**  
   - COM1/NO1 → Light load terminal  
   - COM2/NO2 → Fan load terminal  
   - COM3/NO3 → Door actuator motor/solenoid  

4. **AC Mains**  
   - Neutral → COM pins  
   - Live → NO pins (switched by relay)  

5. **Common Ground**  
   - Ensure all GNDs (NodeMCU, relay module, power supply) are tied together.

---

## Software Setup

### 1. Install Arduino IDE & ESP8266 Support

1. Open **Arduino IDE** → **File → Preferences**  
2. Add Additional Boards URL:  
