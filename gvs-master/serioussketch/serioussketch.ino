#include <DueTimer.h>
#include <MPU9250.h>
float gY = 0;          //Angular velocity around y axis in rads/sec
float gX = 0;
float gZ = 0;
float aY = 0;          //Acceleration in m/s^2
float aX = 0;
float aZ = 0;
int mode = 0;
int outputValue = 0;    //Holds value to be written to analog output
float gain = 0;    //User specified constant for function
float steadyVoltage = 0;
int analogOut = DAC0;     //Pin for analog output voltage
int analogRef = DAC1;     //to enable refrence of 0.57V since 0V is impossible on DACs
int analogIn = A0;        //Pin to read in voltage from the electrodes
int voltageIn = 0;              //variable to contain analog read value (0-1023)
float outputInVolts;
MPU9250 IMU(Wire,0x68);

using namespace std;


  
void read_string() 
{
  if (Serial3.available()) 
    Serial.println(Serial3.readString()); //first reads from arduino antenna then print to serial output

}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial3.begin(115200);
  IMU.begin();
  // analogWriteResolution(12);


}


void loop() {
  float* arrayValues[7];
  IMU.readSensor();
  // gY = IMU.getGyroY_rads();  
  // gX = IMU.getGyroX_rads();
  // gZ = IMU.getGyroZ_rads();
  // aX = IMU.getAccelX_mss(); 
  // aY = IMU.getAccelY_mss(); 
  // aZ = IMU.getAccelZ_mss();
  read_string();  
  analogWrite(DAC0, 0);
  analogWrite(DAC1, 0);
  delay(10000);
  analogWrite(DAC0, 254);
  delay(10000);
  // assign_imu(&gX, &gY, &gZ, &aX, &aY, &aZ); 
}


void assign_imu(float* gX, float* gY, float* gZ, float* aX, float* aY , float* aZ) { 

  Serial.print("gyro x: ");
  Serial.println(*gX);
  Serial.print("gyro y: ");
  Serial.println(*gY);
  Serial.print("gyro z: ");
  Serial.println(*gZ);
  Serial.print("accel x: ");
  Serial.println(*aX);
  Serial.print("accel y: ");
  Serial.println(*aY);
  Serial.print("accel z: ");
  Serial.println(*aZ);
  delay(1000);
}




//   // arrayValues[6] {&gY, &gX, &gZ, &aY, &aX, &aZ}
//   // for ( int i = 0; i < 6; i++) 
//   // {
//   //   Serial.println(arrayValues[i]);
//   // }

// }
