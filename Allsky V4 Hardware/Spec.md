# Allsky Camera V4 Specification

## Mechanical
The following mechanical design features:
- Pan & Tilt Camera head
- 4 Legged Design with adjustable legs
- Fixed Solar Panels

## Electrical
- Main Pi PCB
    - 5V Supply 
    - GPS (SAM-M10Q-00B)
    - Heater Control
        - Fan
        - Temperature Sensor
        - Heat Control
    - Stepper Motor control
    - Status LED
- Sensor PCB
    - IMU
    - Temperature Sensor
    - Humidity Sensor (BME280)
- Separate Solar PCB with RS-232 (to replace with own MPPT controller in future)
    - Input Voltage & Current Sense
    - Output Voltage & Current Sense

