#include <DueTimer.h>
#include <MPU9250.h>
/* 
 * 

 */
int START_SIGNAL = 41;
int ENTER_MODE_SIGNAL = 42;
int NO_INPUT_NEEDED = 43;
int PROMPT_FOR_VOLTAGE = 44;
int PROMPT_FOR_GAIN = 45;
int FIVE_SECONDS_OF_DATA_RECIEVED = 46;

float gyroY;          //Angular velocity around y axis in rads/sec
float gyroX;
float gyroZ;
float accelY;          //Acceleration in m/s^2
float accelX;
float accelZ;
int mode;
int outputValue = 0;    //Holds value to be written to analog output
float gain = 0;    //User specified constant for function
float steadyVoltage = 0;
int analogOut = DAC0;     //Pin for analog output voltage
int analogRef = DAC1;     //to enable refrence of 0.57V since 0V is impossible on DACs
int analogIn = A0;        //Pin to read in voltage from the electrodes
int voltageIn = 0;              //variable to contain analog read value (0-1023)
float outputInVolts;
MPU9250 IMU(Wire, 0x68);    //Initalize imu Serial communication with address 0x68
byte buffer_for_incoming_bytes[4];
boolean dataRequiredFlag = false;
unsigned long timeStamp;




void sendDataFlag(){

  dataRequiredFlag = true;

}



void setup() {

  Serial2.begin(115200);
  Serial.begin(115200);
  int status = IMU.begin();   //Initalize connection to IMU
  analogWrite(analogRef,0);   //Initalize reference to 0.57V
  outputValue = 0;             //Ensure output value is initalized to zero during setup
  analogWrite(analogOut,outputValue);   //Ensure output value of 0 is written to the analog output
  
  
  if(status <  0){        //Ensure connection was succesful
    Serial.print("IMU initalization was unssuccesfull status =: ");
    Serial.print(status);  //Print error message
    while(1){}          //If connection was unsuccessful wait forever
  }

  Serial.println("IMU was initalized");

  sendInteger(&START_SIGNAL);

  setup_mode();
}



//This function maps integer value of voltage from arduino to real voltage value
float integer_to_voltage(int integer){
  return (float((3.3-0.57)/255.))*float(integer);
}

//This function maps real voltage values to integer values understood by arduino
int voltage_to_integer(float voltage){ 
  return 255/(3.3-0.57)*voltage;
}



void zero_voltage(){
    outputInVolts = 0;
    outputValue = voltage_to_integer(outputInVolts);
    analogWrite(analogOut,outputValue); 
      
}

void steady_voltage(){
  
  outputValue = voltage_to_integer(outputInVolts);
  analogWrite(analogOut, outputValue);
    
}


//Function which writes output on the analog out pin as a function of the rotational movement arount the y axis
void proportional_voltage(){

  if(gyroY > 0){    //Only send voltage if rotation is in the positive direction
    
    outputValue = (int)(gain * gyroY);
    outputInVolts = integer_to_voltage(outputValue);
    
  }else{
    
    outputValue = 0;
    
  }   

  if(outputValue > 0 && outputValue < 255){                      //Write output onto analog pin
      
    analogWrite(analogOut, outputValue);
    
  }else if(outputValue <= 0){
    outputValue = 0;    
    analogWrite(analogOut, outputValue);
    
  }

  
}








//infinite loop tasked with waiting for user input
//user can change mode and this loop will change the global mode variable and call the necessary setup routine
void loop() {
  
  if(Serial2.available() > 0){    //This will pick up when user has pressed any key

    Serial2.flush();
    setup_mode();
  
  }

  if(dataRequiredFlag){    
      
    IMU.readSensor(); 

    timeStamp = micros();
    gyroX = IMU.getGyroX_rads();
    gyroY = IMU.getGyroY_rads();
    gyroZ = IMU.getGyroZ_rads();
    accelX = IMU.getAccelX_mss();
    accelY = IMU.getAccelY_mss();
    accelZ = IMU.getAccelZ_mss();

  
    sendPackage(&gyroX,&gyroY,&gyroZ,&accelX,&accelY,&accelZ, &outputInVolts, &timeStamp);

    dataRequiredFlag = false;
  
  }



  if(mode == 3){
    
    zero_voltage();
    
  }else if(mode == 1){
    
    steady_voltage(); //
    
  }else if(mode == 2){
    
    proportional_voltage();
    
  }else{
    
    setup();    //If any other character was input reprompt user for mode 
    
  }

  analogWrite(analogRef,0);          //Ensure reference remains steady


}

//timer interrupt service routine
//sends imu data at 100hz



