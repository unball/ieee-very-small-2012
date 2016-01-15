  // DEFINIÇÃO DO ROBO
 #define this_robot 0 // diretriz que informa qual o numero de cada robo - cada robo recebera um diferente 
 
 
 //DEFINIÇÕES DOS PINOS PONTE H
  //Motor A Direito
  const int mDir1 = 13;  
  const int mDir2 = 12;    
  const int enableDir = 10;  
  //Motor B Esquerdo
  const int mEsq1 = 11;    
  const int mEsq2 = 8;    
  const int enableEsq = 9;    
 
 int pwm=0;


void cponte(int pino1, int pino2 );

  void setup() {
    pinMode(mDir1, OUTPUT); 
    pinMode(mDir2, OUTPUT); 
    pinMode(enableDir, OUTPUT);
    pinMode(mEsq1, OUTPUT); 
    pinMode(mEsq2, OUTPUT); 
    pinMode(enableEsq, OUTPUT);
  }

  void loop() {
    
      digitalWrite(mDir1, HIGH);  // Frente
      digitalWrite(mDir2, LOW);
      digitalWrite(mEsq1, HIGH);  
      digitalWrite(mEsq2, LOW);
    
for(pwm=0;pwm<=250;pwm+=10){
  analogWrite(enableDir, pwm); 
  analogWrite(enableEsq, pwm);
  delay(500);
}

delay (3000);
 pwm=0;
 
      digitalWrite(mDir1, LOW);  //Tras
      digitalWrite(mDir2, HIGH);
      digitalWrite(mEsq1, LOW);  
      digitalWrite(mEsq2, HIGH);
    
for(pwm=0;pwm<=250;pwm+=10){
  analogWrite(enableDir, pwm);
  analogWrite(enableEsq, pwm);
   delay(500); 
}

delay (3000);
pwm=0;
    
}

