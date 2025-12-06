# Mini Bluetooth-Controlled Balancing Robot Chassis

## Description
A small chassis for a wheeled balancing robot. Its two Nidec 24H motors have built-in encoders and are powered by a thin 2200mAh LiPo. The GY-BNO055 IMU provides the ESP32 with orientation feedback for balancing. It can be controlled by Bluetooth commands.

## Why?
I tried building a balancing robot in the past for a hardware hackathon. It used NEMA17 stepper motors. It sucked and probably wouldn't have ever worked. That's why I want to make one that uses BLDC motors and actually works.

## The Model
<img width="566" height="542" alt="Screenshot 2025-12-06 142607" src="https://github.com/user-attachments/assets/81f08577-f7f2-4be9-b4ce-e30f0381fb1a" />
<img width="356" height="507" alt="Screenshot 2025-12-06 142533" src="https://github.com/user-attachments/assets/1676a031-4bb8-49dd-8538-0b3a75167ee3" />
<img width="392" height="599" alt="Screenshot 2025-12-06 142515" src="https://github.com/user-attachments/assets/0e064c2c-cafa-4cac-99fc-12340ae5f702" />
<img width="524" height="563" alt="Screenshot 2025-12-06 142403" src="https://github.com/user-attachments/assets/3127ebd4-9c73-482e-b366-7524f42454d5" />


## Wiring Diagram
<img width="768" height="608" alt="Screenshot 2025-12-05 211010" src="https://github.com/user-attachments/assets/f1f324d8-4eab-466d-b8ce-2751e5e9cb0a" />

## BOM:
Links here: https://docs.google.com/spreadsheets/d/15BZOgCAK9HfxFjphhOrtfexejHQh9IfhAeZVUUb6IY0/edit?usp=sharing

| Item | Purpose | Item Type | Order Amount | Cost |
|---|---|---|---|---|
| jumpers | Wiring components | N/A | 1 | $5.99 |
| gy-bno055 | Sensing orientation | N/A | 1 | $13.18 |
| lm2596 | Powering the ESP32 | 1 PCS | 1 | $1.71 |
| nidec 24h055mo20 | Driving the wheels | N/A | 2 | $17.54 |
| esp32 devboard | Controlling the robot | ESP32 Type-C 30Pin | 1 | $4.17 |
| 15x28x7 mm bearing | Low-friction wheel hubs | 4, 6902-2RS 15mmx28mmx7mm | 1 | $6.99 |
| m2.5x10 screws | Securing the motors | M2.5 50PCS, x10mm | 1 | $2.27 |
| m3x5 tapping screws | Mounting the LM2596 | M3 x 50Pieces, 5mm | 1 | $1.50 |
| m3x8 tapping screws | Mounting the drive modules and ESP32 | M3x8mm, 20pcs | 1 | $1.40 |
| silicone bands | High-friction tires | Any | 1 | $7.99 |
| 3S LiPo | Powering the robot | 1Pcs | 1 | $19.89 |
| 10uF ceramic capacitor | Protect ESP32 from current spikes | N/A | 1 | $0 |
| 220uF electrolyitc capacitor | Protect ESP32 from current spikes | N/A | 1 | $0 |
