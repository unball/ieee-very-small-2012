//Teste eco Xbee
int flag=0;
byte incomingByte;
 
 void setup()
 {
   Serial.begin(9600);
   Serial.println("INICIANDO");
   pinMode(A5,OUTPUT);
 }
 
 void loop()
 {
   
   if(Serial.available() > 0) 
   {
      // read the incoming byte:
      incomingByte = Serial.read();
      Serial.write(incomingByte);  
      if (flag==1){
      digitalWrite(A5,HIGH);
      flag=0;}
      else { 
      digitalWrite(A5,LOW);
      flag=1;} 
   } 
   delay(10);
 }

