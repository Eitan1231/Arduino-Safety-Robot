# Arduino Safety Robot

This project demonstrates how to integrate multiple sensors and actuators on Arduino for a **collision-avoidance and pressure-responsive system**.  
It combines **DC motors**, **FSR402 force sensors**, an **HC-SR04 ultrasonic sensor**, and a **relay-controlled air pump** into one working prototype.

---

## 🔧 Features
- **Dual DC motor control** with PWM (speed & direction).
- **FSR402 sensors** detect force/pressure and dynamically adjust motor speed.
- **HC-SR04 ultrasonic sensor** measures distance and stops motors if an obstacle is too close.
- **Relay module with air pump** simulates an external reaction system.
- **Failsafe logic**: obstacle detection (< 15 cm) immediately stops motors and disables the pump.

---

## 📂 Hardware Components
- Arduino Uno (or compatible board)
- 2x DC motors with motor driver (e.g., L298N or L293D)
- 2x FSR402 force sensors
- 1x HC-SR04 ultrasonic sensor
- 1x Relay module + air pump
- Wires, breadboard, and power supply

---

## ⚙️ How It Works
1. **Ultrasonic Sensor (HC-SR04)**  
   - Continuously measures the distance to obstacles.  
   - If distance < 15 cm → motors stop for 4 seconds.  

2. **Force Sensors (FSR402)**  
   - If both sensors read **below threshold**:  
     - Motors accelerate gradually (`+10 PWM` each loop, capped at max).  
     - Relay turns **ON**, activating the air pump.  
   - If either sensor reads **above threshold**:  
     - Motors stop immediately.  
     - Relay turns **OFF**.  
     - Speed resets to base level (50).  

3. **Motors**  
   - Controlled with PWM for smooth acceleration.  
   - Stop automatically when safety conditions are triggered.  

4. **Relay + Pump**  
   - Relay drives an external air pump.  
   - Pump only works when system is in “safe” state (clear path + low FSR values).  

5. **Failsafe Logic**  
   - Default speed starts at `50`.  
   - After an obstacle or overload, speed resets back to safe level.  
   - Serial Monitor prints real-time data (`Distance`, `FSR values`, `Current Speed`).  

---

## 🚀 How to Run This Project

1. **Clone the repository**  
   ```bash
   git clone https://github.com/<your-username>/Arduino-Safety-Robot.git
   cd Arduino-Safety-Robot
