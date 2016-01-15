byte Byte = 0;         // incoming serial byte

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Serial.println("H ou L");
}




void loop()
{
  
  if (Serial.available() > 0) { 

Byte=Serial.read();


  Serial.write(Byte);//mudar para WRITE  
}
}
