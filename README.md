# Maze-E | The Maze Solving Robot 🤖
<img align = "left" src="https://user-images.githubusercontent.com/24956953/218305250-4088d624-5d7e-4277-a687-449090a5087a.jpeg" width="320" />
An Arduino based two wheeled robot that follows a line and also avoids dead ends to solve a maze.
Sensors and modules used:<br>
<b>
- Arduino Uno<br>
- L298N Motor Driver<br>
- IR sensor module<br>
- LM393 with Optical Sensor <br>
</b>
<br>
Full explanation and reasons behind various design choices (eg: why 2 wheels and not 4) are explained below. <br>
P.s. I named it after Wall-E :)<br><br>

https://user-images.githubusercontent.com/24956953/218301083-9bb2f885-cff9-4507-8e3a-912ace56658b.mp4

Above video shows a timelapse of it solving a maze I built. Please note that the Ultrasonic sensor and the LCD screen are additional components for other purposes and are not necessary for Maze-E to perform. The code sections responsible for them have been removed from the code. 

Components Used
--------

1. Arduino Uno (any basic arduino board should work)
2. 2WD round robot diy chassis kit with two wheel encoders
3. L298N motor driver
4. 5 IR sensors (sensor placement explained below)
5. 2 LM393 with Optical Sensors / IR speed sensors 
6. 18650 3.7v batteries (2 is sufficient but 3 is optimal)
7. 18650 Battery holder 
8. Push button (to control start)
9. Switch (to turn on/off power)
