# Allsky Camera V4 Specification

## Mechanical
The following mechanical design features:
- Pan & Tilt Camera head
- 4 Legged Design with adjustable legs
- Fixed Solar Panels

## Electrical
- Main Pi PCB
    - GPS
    - Heater Control
        - Fan
        - Temperature Sensor
        - Heat Control
    - Stepper Motor control
    - Status LED
- Sensor PCB
    - IMU
    - Temperature Sensor
- Separate Solar PCB with RS-232 (to replace with own MPPT controller in future)
    - Input Voltage & Current Sense
    - Output Voltage & Current Sense