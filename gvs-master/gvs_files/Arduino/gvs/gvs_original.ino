#include <MPU9250.h>
/* High Level: This program takes input from a gyroscope and the user via the serial monitor and
 *  outputs a analog voltage value on DAC0 pin.
 * 
 * Details: Initaly the user is prompted to input a decimal gain value.  The Arduino reads the current angular acceleration in rads/sec around the y-axis of the IMU
 * each time the loop executes. An analog write to the DAC0 pin maps integer values from 0 to 255 to voltage outputs of 0V to 3.3V 
 * At the end of each execution of the loop the gyro measurement is multiplied by the users specified gain and converted to an integer.
 * This integer is written to the output value DAC0. 
 */

float gyroY;          //Angular velocity around y axis in rads/sec
float gyroX;
int outputValue = 0;    //Holds value to be written to analog output
float gain = 0;    //User specified constant for function
int analogOut = DAC0;     //Pin for analog output voltage
int analogIn = A0;        //Pin to read in voltage from the electrodes
int voltageIn = 0;              //variable to contain analog read value (0-1023)
float realVoltage = 0;            //variable to contain the real voltage (0V-5V)
int outputInVolts;
MPU9250 IMU(Wire, 0x68);    //Initalize imu Serial communication with address 0x68

// Max GVS output= 2.76V; lowest output = 0.56V (mapped from 0 to 255)

void setup() {

  Serial.begin(115200);
  int status = IMU.begin();   //Initalize connection to IMU
  analogWrite(DAC0,0);
  
  if(status <  0){        //Ensure connection was succesful
    Serial.print("IMU initalization was unssuccesfull status =: ");
    Serial.print(status);
    while(1){}          //If connection was unsuccessful wait forever
  }

  /* Serial.print("Enter gain: ");
  int recieved = 1;                   
  while(recieved){                    //Wait for user to input to set gain 
  if(Serial.available() > 0){
    gain = Serial.parseFloat();
    recieved = 0;    
  }
  }
  */
  

  gain = 250.0;

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){  
    gain = Serial.parseFloat();  
  }


  IMU.readSensor();                 //Get gyro reading around y-axis
  gyroX = IMU.getGyroX_rads();
  gyroY = IMU.getGyroY_rads();
// Serial.print("Gyro Y is: ");      //Display gyro reading
// Serial.print(gyroY, 6);
// Serial.print("\n");

  analogWrite(DAC1,0);

//Read analog voltage

//voltageIn = analogRead(analogIn);
//realVoltage = (5./1023.)*voltageIn;
//Serial.print("The current is: ");
//Serial.print(realVoltage*10.);
//Serial.print("\n");


if(gyroY > 0){    //Only send voltage if rotation is in the positive direction; negative direction = 0V output
  outputValue = (int)(gain * gyroY);
  Serial.print(gain);
  Serial.print(gyroY);
  Serial.print(outputValue);
}else{
  outputValue = 0;
}   

   //Calculate output based on rotation and user input
  if(outputValue > 0 && outputValue < 116){                      //Write output onto analog pin. Use the formula (X / 255 = Voltage Desired / 2.2V) sets output limit.
    analogWrite(analogOut, outputValue);
  }else if(outputValue <= 0){
    analogWrite(analogOut, 0);
  }

Serial.print("Voltage output is: ");
Serial.print((2.76-0.56)/255.*outputValue);
Serial.print(" ");
Serial.print("\n");

  delay(0);//set delay to so that serial monitor is readable

}

