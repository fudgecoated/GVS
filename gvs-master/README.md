This code can be run using the arduino IDE found here: https://www.arduino.cc/en/main/software.

The library used to interface with the MPU9250 imu chip can be found here: https://github.com/bolderflight/MPU9250

The code will output a voltage between 0 and 2.2V based on the reading from the IMU. To start the output one must first enter a gain via the serial monitor. To get reasonable output the gain can be set between 100 and 300.

When used with the differential amplifier in current mode every volt will cause a milliamp of current.

Practicalities of running Arduino IDE

Initial use:
-insert USB cable in port closest to power cord on Arduino
-in Arduino IDE, go tools->manage libs->search mpu9250; install the one by bolderflights
-in Arduino IDE, go tools->boards->board manager, search for 'due' and install
-go tools->board; select Arduino due (programming port)
-go tools->port; select Arduino (when Arduino connected to PC)
-in Serial Monitor (magnifying glass), set baud to 115200

Wireless use:
-insert USB cable in port closest to power cord on Arduino
-Connect to wixel using usb cable.
-insert power source positive terminal into Vin and negative terminal to any
ground pin on the arduino.
-in Arduino IDE, go tools->manage libs->search mpu9250; install the one by bolderflights
-in Arduino IDE, go tools->boards->board manager, search for 'due' and install
-go tools->board; select Arduino due (programming port)
-go tools->port; select Arduino (when Arduino connected to PC)
-disconnect usb cable from arduino
-using the terminal open up the serial port where the wixel is
connected.(Python program comming soon)
 


Running IDE
-to run: '->' button, uploads program to Arduino (takes a while ...), program will start running 
-Red button (reset) on arduino temporarily switches program off, while holding down, restarts when button is released
-To stop completely (or troubleshoot/kill): hold black (erase) button down for 3 s, then hold down reset button for 3 s

Connecting amplifyer:
-header pin cord most left side (most glue) goes into DAC0 on the arduino board (this ensures RED electrode is hot (-), black is ground)
-Connect female monoJack to male input jack on amp
-Connect battery to amp; use 4 thing cable (BLUE hook on RED battery pole!!)

Amplifyer safety:
-Never wire across the heart (best place to test is on single leg)
-NEVER unplug anything while connected to subject, nor switch off amp
-in protect mode (red light), the amp seems to be safe, you can attach electrodes to the participant, while in protect mode
-Whenever running program: initially start in Voltage mode and always keep Zout at 1 kOhm
-When everything is securely attached, run 0V program
-hold reset button for 3 s on back of amp, protect light goes off (while running 0 V)
-Then switch into Current mode
-Now run other programs
-The amp will switch into protect mode when Voltage exceeds 200 V (happens any time in current mode with high impedance)

(Emerency) stopping the program:
-Run zero Volt program (will overwrite, takes some time, can run into compilation error)
-Press black (erase) for 3s, then red (reset) button 3s
 
Taking off electrodes:
-Run zero Volt program
-Set amp to Voltage mode
-Take hot (red) electrode off first, without touching metal part
-Then take black electrode off
-Now switch amp off






