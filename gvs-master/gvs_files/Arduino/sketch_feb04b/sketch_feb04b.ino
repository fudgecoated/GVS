

int analogOut = DAC0;
int ground = DAC1;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  analogWrite(ground, 0);
}

void loop() {
  // put your main code here, to run repeatedly:


  analogWrite(analogOut, 58); // All the numbers from 0 to 255 are mapped 0 to 2.2V (eg. can produce 2.2V). If you want to output 2V, you need a proportion: (X/256 = 2V/2.2V), solve for X
}
