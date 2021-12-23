 

int analogOut = DAC0;
int ground = DAC1;



void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  analogWrite(ground, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

  analogWrite(analogOut, 0);

}
