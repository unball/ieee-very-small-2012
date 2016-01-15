
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
  float pesquisa_vel[] = {0, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500}; 
  volatile unsigned long contador=0;
  int pwmEsq=0;
  int pwmDir=0;
  float instEsq=0;
  float instDir=0;
  float erroEsq=0;
  float erroDir=0;
  float refEsq=0;
  float refDir=0;
  
 // Variaveis de tratamento do byte recebido serialmente
 byte incomingByte = 0;	// for incoming serial data
 unsigned int rc_robo = 0; // variavel para receber para qual robo eh a informacao
 unsigned int rc_roda = 0; // 0 esqerda 1 direita
 unsigned int rc_sign = 0; // 0 frente 1 tras
 unsigned int rc_vel = 0; // vel recebida

void cponte(int pino1, int pino2 );


  void setup() {
    interrupts();
    Serial.begin(9600);
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

void leitura(){
  if(Serial.available() > 0) 
   {
      // read the incoming byte:
      incomingByte = Serial.read();
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, BIN); // Imprime o byte em si.

      rc_robo  = (incomingByte>>6) & B00000011;
      Serial.print("Robo: ");
      Serial.println(rc_robo, DEC); // Imprime o byte em si.
      
      if (rc_robo==this_robot){
        
      rc_roda = (incomingByte>>5) & B00000001;
      Serial.print("Roda: ");
      Serial.println(rc_roda, DEC); // Imprime o byte em si.
        
      rc_sign = (incomingByte>>4) & B00000001;
      Serial.print("Sign: ");
      Serial.println(rc_sign, DEC); // Imprime o byte em si.

      rc_vel  = incomingByte & B00001111;
      Serial.print("PWM: ");
      Serial.println(rc_vel, DEC); // Imprime o byte em si.  
      Serial.println(pesquisa_vel[rc_vel],DEC);    
    
      if(rc_roda==0){
        refEsq=pesquisa_vel[rc_vel]; //atualiza referencia roda esquerda
        cponte(mEsq1, mEsq2);//atualiza valores da Ponte H
      }
      else {           //idem para roda direita
        refDir=pesquisa_vel[rc_vel];
        cponte(mDir1,mDir2); 
       }
      
      } else Serial.println("Nao eh este robo");
    
 }
  
  
  
}
void cponte(int pino1, int pino2 ){//controle ponte H

    if (rc_vel==0) {
      digitalWrite(pino1, LOW);  // PARA
      digitalWrite(pino2, LOW);
    } 
    else if(rc_sign==0){
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
delay(10);
detachInterrupt(0);//digital pin 2
instEsq=(contador-1-contador*0.03)/512.0*100.0*60.0;
Serial.write("Velocidade Esquerda=");
Serial.println(instEsq);
//RODA DIREITA
contador=0;
attachInterrupt(1, soma, RISING);//digital pin 3
delay(10);
detachInterrupt(1);//digital pin 3
instDir=(contador-1-contador*0.03)/512.0*100.0*60.0;
Serial.write("Velocidade Direita=");
Serial.println(instDir);

} 
 

void cvelocidade(){

//CONTROLE RODA ESQUERDA
if (refEsq!=0){
erroEsq=refEsq-instEsq;
if(erroEsq>100){
  pwmEsq++;
 if(erroEsq>1000)
 pwmEsq+=4;
 if (pwmEsq>255)
pwmEsq=255;
if (pwmEsq<5)
pwmEsq=5;
}
else if (erroEsq<-100){
  pwmEsq--;
 if(erroEsq<-1000)
 pwmEsq-=4;
if (pwmEsq<5)
pwmEsq=5;
}
}
else pwmEsq=0;


Serial.write("PWM Esquerda=");
Serial.println(pwmEsq);
analogWrite(enableEsq, pwmEsq); 

//CONTROLE RODA DIREITA
if (refDir!=0){
erroDir=refDir-instDir;
if(erroDir>100){
  pwmDir++;
 if(erroDir>1000)
 pwmDir+=4;
 if (pwmDir>255)
pwmDir=255;
if (pwmDir<5)
pwmDir=5;
}
else if (erroDir<-100){
  pwmDir--;
 if(erroDir<-1000)
 pwmDir-=4;
if (pwmDir<5)
pwmDir=5;
}
}
else pwmDir=0;


Serial.write("PWM Direita=");
Serial.println(pwmDir);
analogWrite(enableDir, pwmDir); 
}

void soma(){
contador++;
}

