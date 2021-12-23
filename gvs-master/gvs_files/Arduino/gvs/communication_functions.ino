
void sendInteger(int* data){
  byte* byteData = (byte*)(data);
  Serial2.write(byteData, 4);
}

void sendFloat(float* data){
  byte* byteData = (byte*)(data);
  Serial2.write(byteData,4);
}

void sendPackage(float* gyroX, float* gyroY, float* gyroZ, float* accelX, float* accelY, float* accelZ, float* voltage, unsigned long* timeStamp){
  byte* byteData1 = (byte*)(timeStamp);
  byte* byteData2 = (byte*)(gyroX);
  byte* byteData3 = (byte*)(gyroZ);
  byte* byteData4 = (byte*)(accelX);
  byte* byteData5 = (byte*)(accelY);
  byte* byteData6 = (byte*)(accelZ);
  byte* byteData7 = (byte*)(voltage);
  byte* byteData8 = (byte*)(gyroY);
  byte buf[32] = {byteData1[0], byteData1[1], byteData1[2], byteData1[3],
                 byteData2[0], byteData2[1], byteData2[2], byteData2[3],
                 byteData3[0], byteData3[1], byteData3[2], byteData3[3],
                 byteData4[0], byteData4[1], byteData4[2], byteData4[3],
                 byteData5[0], byteData5[1], byteData5[2], byteData5[3],
                 byteData6[0], byteData6[1], byteData6[2], byteData6[3],
                 byteData7[0], byteData7[1], byteData7[2], byteData7[3],
                 byteData8[0], byteData8[1], byteData8[2], byteData8[3]
                 };
  Serial2.write(buf, 12);
}



int receiveInteger(){
    int incoming_num;
    for(int i = 0; i < 4; i++){
      buffer_for_incoming_bytes[i] = Serial2.read();
      delay(10);
    }
    
    incoming_num = (int) buffer_for_incoming_bytes[3] << 24;
    incoming_num |=  (int) buffer_for_incoming_bytes[2] << 16;
    incoming_num |= (int) buffer_for_incoming_bytes[1] << 8;
    incoming_num |= (int) buffer_for_incoming_bytes[0];

    return incoming_num;
}

float recieveFloat(){
  int incoming_num;
  for(int i = 0; i < 4; i++){
     buffer_for_incoming_bytes[i] = Serial2.read();
     delay(10);
  }

    incoming_num = (int) buffer_for_incoming_bytes[3] << 24;
    incoming_num |=  (int) buffer_for_incoming_bytes[2] << 16;
    incoming_num |= (int) buffer_for_incoming_bytes[1] << 8;
    incoming_num |= (int) buffer_for_incoming_bytes[0];

    return *((float*) &incoming_num);

}
