
  // DEFINIÇÃO DO ROBO 1
 const int this_robot=1; // diretriz que informa qual o numero de cada robo - cada robo recebera um diferente 
 
 
 //DEFINIÇÕES DOS PINOS PONTE H
  //Motor A Direito
  const int mDir1 = 13;  
  const int mDir2 = 12;    
  const int enableDir = 10;  
  //Motor B Esquerdo
  const int mEsq1 = 11;    
  const int mEsq2 = 8;    
  const int enableEsq = 9;    

//DEFINIÇÕES DAS VARIAVES

//Variaveis de controle
  float pesquisa_vel[16] = {0, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000, 9500, 10000}; 
  volatile unsigned long contador=0;
  int pwmEsq=0;
  int pwmDir=0;
  float instEsq=0;
  float instDir=0;
  float erroEsq=0;
  float erroDir=0;
  float refEsq=0;
  float refDir=0;
  float erroIntegralEsq=0, erroIntegralDir=0;
  float erroDerivativoEsq=0, erroDerivativoDir=0;
  float erroEsqAnt=0, erroDirAnt=0;
  
  
 // Variaveis de tratamento do byte recebido serialmente
 char incomingByte[2] = {0,0};	// for incoming serial data
 unsigned int rc_robo[2] = {0,0}; // variavel para receber para qual robo eh a informacao
 unsigned int rc_roda[2] = {0,0}; // 0 esqerda 1 direita
 unsigned int rc_sign[2] = {0,0}; // 0 frente 1 tras
 unsigned int rc_vel[2] = {0,0}; // vel recebida

int flag=0;


  void setup() {
    interrupts();
    Serial.begin(19200);
    Serial.write("Iniciando");   
    
    // set all the other pins you're using as outputs:
    pinMode(mDir1, OUTPUT); 
    pinMode(mDir2, OUTPUT); 
    pinMode(enableDir, OUTPUT);
    pinMode(mEsq1, OUTPUT); 
    pinMode(mEsq2, OUTPUT); 
    pinMode(enableEsq, OUTPUT);  
  }

  void loop() {
    leitura();
    encoder();
    cvelocidade();
}

void leitura()
{
  if(Serial.available() > 1) 
   {
      // read the incoming byte:
      Serial.readBytes(incomingByte, 2);
      
      rc_robo[0]  = (incomingByte[0]>>6) & B00000011;
      // Tratando o Byte recebido
   
   if (rc_robo[0]==this_robot){
        
      rc_roda[0] = (incomingByte[0]>>5) & B00000001;
      rc_sign[0] = (incomingByte[0]>>4) & B00000001;
      rc_vel[0]  = incomingByte[0] & B00001111;
      Serial.print("PWM: ");
   }
    
//segundo byte
      rc_robo[1]  = (incomingByte[1]>>6) & B00000011;
      // Tratando o Byte recebido
      if (rc_robo[1]==this_robot){
        
      rc_roda[1] = (incomingByte[1]>>5) & B00000001;
      rc_sign[1] = (incomingByte[1]>>4) & B00000001;
      rc_vel[1]  = incomingByte[1] & B00001111;  
    }
  
 if(rc_robo[0]!=rc_robo[1])
 {
      if(Serial.available()>0)Serial.read();
  // Serial.println("Robos nao bateram");
 }
 
else if(rc_roda[0]!=0 || rc_roda[1]!=1)
 {
   if(Serial.available()>0)Serial.read();
   //   Serial.println("Rodas nao bateram");
 }
 
else {
  
        refEsq=pesquisa_vel[rc_vel[0]]; //atualiza referencia roda esquerda
        cponte(mEsq1, mEsq2, 0);//atualiza valores da Ponte H
  
        refDir=pesquisa_vel[rc_vel[1]];
        cponte(mDir1,mDir2, 1); 
    
        debug();
      }  

   }
}//leitura();
  
  
  
void cponte(int pino1, int pino2, int roda ){//controle ponte H

    if (rc_vel[roda]==0) {
      digitalWrite(pino1, LOW);  // PARA
      digitalWrite(pino2, LOW);
    } 
    else if(rc_sign[roda]==0){
      digitalWrite(pino1, HIGH);  // FRENTE
      digitalWrite(pino2, LOW);   
    }
    else {
      digitalWrite(pino1, LOW);   // TRAS
      digitalWrite(pino2, HIGH);  
    }     
}   


   
void encoder(){
//RODA ESQUERDA
contador=0;
attachInterrupt(0, soma, RISING);//digital pin 2
delay(5);
detachInterrupt(0);//digital pin 2
instEsq=(contador)/512.0*200.0*60.0;
//Serial.write("Velocidade Esquerda=");
//Serial.println(instEsq);
//RODA DIREITA
contador=0;
attachInterrupt(1, soma, RISING);//digital pin 3
delay(5);
detachInterrupt(1);//digital pin 3
instDir=(contador)/512.0*200.0*60.0;
//Serial.write("Velocidade Direita=");
//Serial.println(instDir);

} 
 

void cvelocidade()
{
//CONTROLE RODA ESQUERDA
  if (refEsq!=0){
    erroEsq=refEsq-instEsq;
    erroIntegralEsq = erroIntegralEsq + erroEsq;
    erroDerivativoEsq =  erroEsq - erroEsqAnt;
    pwmEsq=(erroEsq*0.23*255/10000) + (erroIntegralEsq*0.06*255/10000) + (erroDerivativoEsq*0.005*255/10000);  
    if (pwmEsq>255)
      pwmEsq=255;
    if (pwmEsq<5)
      pwmEsq=5;
  }
  else pwmEsq=0;
  analogWrite(enableEsq, pwmEsq);

  //CONTROLE RODA DIREITA
  if (refDir!=0){
    erroDir=refDir-instDir;
    erroIntegralDir = erroIntegralDir + erroDir;
    erroDerivativoDir = erroDir - erroDirAnt;
    pwmDir=(erroDir*0.23*255/10000) + (erroIntegralDir*0.06*255/10000) + (erroDerivativoDir*0.005*255/10000);
    if (pwmDir>255)
      pwmDir=255;
    if (pwmDir<5)
      pwmDir=5;
  }
  else pwmDir=0;
  analogWrite(enableDir, pwmDir);
}

void soma(){
contador++;
}

void debug ()
{
  if(flag==1)
    {
     digitalWrite(A5, HIGH); 
     flag=0; 
    }
   else
    {
     digitalWrite(A5, LOW); 
     flag=1;
    }
}
