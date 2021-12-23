
//Get gain from user
void prompt_user_for_gain(){
  sendInteger(&PROMPT_FOR_GAIN);
  Serial.print("Enter gain: ");
  boolean recievedGain = false;                   
  while(!recievedGain){        
  if(Serial2.available() > 0){
    gain =  recieveFloat();
    recievedGain = true;
    Serial.print("gain is: ");
    Serial.println(gain);
  }
  }
}


//Get voltage from user
void prompt_user_for_voltage(){
  sendInteger(&PROMPT_FOR_VOLTAGE);
  Serial.print("Enter voltage");
  boolean recievedVoltage = false;
  while(!recievedVoltage){                
    if(Serial2.available() > 0){
      outputInVolts =  recieveFloat();
      Serial.print("voltage entered is: ");
      Serial.println(outputInVolts);

      //Ensure voltage is within possible values of 0 and (3.3-0.57)
      if(outputInVolts <= 0 || outputInVolts > (3.3-0.57)){               
        Serial.print("The voltage you enter must be greater than 0 and less than 2.73");
      }else{
        recievedVoltage = true;
      }
    }
  }

    Serial.print("voltage is: ");
    Serial.println(outputInVolts);
  
}


void setup_mode(){
    

  Serial.println("Enter Mode:\r\n\t 1 for steady voltage \r\n\t 2 for proportional voltage \r\n\t 3 for no voltage");

  boolean recievedMode = false; 

  //Get mode from user
  while(!recievedMode){
    if(Serial2.available() > 0){
      Serial.println("mode recieved");
      mode = receiveInteger();
      Serial.println("mode " + mode);
      recievedMode = true;
    }
  }

  //configure timer interrupt routine
  Timer2.attachInterrupt(sendDataFlag).start(1000);  //1000 microseconds = 1 milisecond



  if(mode == 1){
    prompt_user_for_voltage();
    Serial.println("mode 1");
    
  }

  
 if(mode == 2){
  prompt_user_for_gain();
  Serial.println("mode 2");
 }

 if(mode == 3){
  sendInteger(&NO_INPUT_NEEDED);
  Serial.println("mode 3");
 }

 Serial2.flush();
  
}

