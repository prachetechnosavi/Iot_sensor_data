# Iot_sensor_data
With this project you can send sensor data from ESP12f board to client device like smartphone, laptop or PC. 
I am using websocket protocol in this project because it updates all clients simultaneously if a change is made.

<h2>Software required</h2><p>Arduino IDE<br><br></p>
<h2>Libraries required</h2><br>1. ESP8266WiFi.h<br>2. ESPAsyncTCP.h<br>3. ESPAsyncWebServer.h<br>4. Arduino_JSON.h

<h2>Circuit Diagram</h2>

![Schematic_IoT_sensor_esp12f_2023-12-31 (1)](https://github.com/prachetechnosavi/Iot_sensor_data/assets/64555378/dbb566fe-f657-4451-81b2-9fdf27dfaf17)

Connect the sensors to ESP12F board as per the schematic diagram given above. 
There are two sensors:<br> 1. HCSR04 to measure distance (Digital output)<br> 2. LDR to meaure light intensity (Analog output) 
                     

