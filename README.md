# Smoke_Detector
A smoke detection system built with Arduino Nano. It uses a smoke sensor module to detect smoke and triggers an alarm or notification, providing a reliable solution for monitoring and alerting against fire hazards.
First, let’s see how this project works. The MQ2 sensor detects smoke and Carbon Monoxide values and sends them to Arduino. Arduino then processes these values and displays these values on the OLED display. It also checks if these values are above the safe level then it sends a command to the buzzer and a LED. Then the buzzer starts alarming with a flashing LED.
