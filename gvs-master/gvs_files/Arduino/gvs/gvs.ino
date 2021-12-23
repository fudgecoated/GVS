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
int highOutput = 2;           //This pin will keep a steady high output which will feed into the button;
int readOutput = 3;           //This pin will read the output of the button
int buttonPressed = 0;
boolean programStatus = true;   //If the boolean is set to true then program will execute IMU dicated output. Else it will be steady current.
MPU9250 IMU(Wire, 0x68);    //Initalize imu Serial communication with address 0x68


void setup() {

  Serial.begin(9600);
  int status = IMU.begin();   //Initalize connection to IMU
  analogWrite(DAC0,0);


  pinMode(highOutput, OUTPUT);
  pinMode(readOutput, INPUT);

  digitalWrite(highOutput, HIGH);
  
  if(status <  0){        //Ensure connection was succesful
    Serial.print("IMU initalization was unssuccesfull status =: ");
    Serial.print(status);
    while(1){}          //If connection was unsuccessful wait forever
  }

    analogWrite(DAC1,0);

  Serial.print("Enter gain: ");
  int recieved = 1;                   
  while(recieved){                    //Wait for user to input to set gain 
  if(Serial.available() > 0){
    gain = Serial.parseFloat();
    recieved = 0;   
  }
  }

}

void loop() {

  buttonPressed = digitalRead(readOutput);

  if(buttonPressed == 1){
    programStatus = !programStatus;
  }

  if(programStatus){
    setOutputFromIMU();
  }else{
    setOutputSteady();
  }

  delay(0);

}



void setOutputFromIMU(){

    if(Serial.available() > 0){
    gain = Serial.parseFloat();
  }


  IMU.readSensor();                 //Get gyro reading around y-axis
  gyroX = IMU.getGyroX_rads();
  gyroY = IMU.getGyroY_rads();


if(gyroY > 0){    //Only send voltage if rotation is in the positive direction
  outputValue = (int)(gain * gyroY);
}else{
  outputValue = 0;
}   

   //Calculate output based on rotation and user input
  if(outputValue > 0 && outputValue < 255){                      //Write output onto analog pin
    analogWrite(analogOut, outputValue);
  }else if(outputValue <= 0){
    analogWrite(analogOut, 0);
  }


}


void setOutputSteady(){

    analogWrite(analogOut, 255);              /This will output maximum current

}


