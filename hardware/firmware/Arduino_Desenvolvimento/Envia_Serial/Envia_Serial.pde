byte Byte = 0;         // incoming serial byte
int Robo=0 ;
int Roda=0;
int Dir=0;
int Vel=0;
int x=0;
int flag=0;

void setup()
{
  // start serial port at 9600 bps:
  Serial.begin(9600);
  Serial.println("Entre o numero do Robo (0 a 2),Roda (0 ou 1),Dir (0 ou 1) e Vel (0 a 15)");
}




void loop()
{
  
  if (Serial.available() > 0) { 
  switch (x){
  case 0: Robo=Serial.read(); Robo-=48;x++; break;
  case 1: Roda=Serial.read(); Roda-=48;x++; break;
  case 2: Dir=Serial.read(); Dir-=48;x++;  break;
  case 3: Vel=Serial.read(); Vel-=48;x=0;flag=0;break; 
  }
 
  switch (Robo){
  case 0: Byte&=B00111111; break;
  case 1: Byte&=B00111111; Byte|=B01000000; break;
  case 2: Byte&=B00111111; Byte|=B10000000; break;
}
  switch (Roda){
  case 0: bitClear(Byte,5); break;
  case 1: bitSet(Byte,5); break;
}
  
  switch (Dir){
  case 0: bitClear(Byte,4); break;
  case 1: bitSet(Byte,4); break;
}  
  switch (Vel){
  case 0: Byte&=B11110000; break;
  case 1: Byte&=B11110000; Byte|=B00000001; break;
  case 2: Byte&=B11110000; Byte|=B00000010; break;
  case 3: Byte&=B11110000; Byte|=B00000011; break;
  case 4: Byte&=B11110000; Byte|=B00000100; break;
  case 5: Byte&=B11110000; Byte|=B00000101; break;
  case 6: Byte&=B11110000; Byte|=B00000110; break;
  case 7: Byte&=B11110000; Byte|=B00000111; break;
  case 8: Byte&=B11110000; Byte|=B00001000; break;
  case 9: Byte&=B11110000; Byte|=B00001001; break;
  case 10: Byte&=B11110000; Byte|=B00001010; break;
  case 11: Byte&=B11110000; Byte|=B00001011; break;
  case 12: Byte&=B11110000; Byte|=B00001100; break;
  case 13: Byte&=B11110000; Byte|=B00001101; break;
  case 14: Byte&=B11110000; Byte|=B00001110; break;
  case 15: Byte&=B11110000; Byte|=B00001111; break;
}
  }
if (flag==0){
  Serial.write(Byte);//mudar para WRITE  
  flag=1;
}
}
