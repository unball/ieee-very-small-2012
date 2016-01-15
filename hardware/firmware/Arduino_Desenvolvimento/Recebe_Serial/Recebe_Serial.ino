 // DEFINIÇÃO DO ROBO
 #define this_robot 1 // diretriz que informa qual o numero de cada robo - cada robo recebera um diferente
 
 int pesquisa_vel[16] = {0, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000, 8500, 9000}; 
char incomingByte[2] = {0, 0};	// for incoming serial data
 
 // Variaveis de tratamento do byte recebido serialmente
 unsigned int rc_robo[2] = {0, 0}; // variavel para receber para qual robo eh a informacao
 unsigned int rc_roda[2] = {0, 0}; // Define qual roda do robo ira aplicar o pwm
 unsigned int rc_sign[2] = {0, 0}; // Sentido da roda escolhida
 unsigned int rc_vel[2] = {0, 0}; // vel recebida
 
 void setup()
 {
   Serial.begin(9600);
   Serial.println("INICIANDO");
     pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
 }
 
 void loop()
 {
   
   if(Serial.available() > 1) 
   {
      // read the incoming byte:
      Serial.readBytes(incomingByte, 2);
      
      
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte[0], BIN); // Imprime o byte em si.

      rc_robo[0]  = (incomingByte[0]>>6) & B00000011;
      Serial.print("Robo: ");
      Serial.println(rc_robo[0], DEC); // Imprime o byte em si.
      // Tratando o Byte recebido
   
   if (rc_robo[0]==this_robot){
        
      rc_roda[0] = (incomingByte[0]>>5) & B00000001;
      Serial.print("Roda: ");
      Serial.println(rc_roda[0], DEC); // Imprime o byte em si.
        
      rc_sign[0] = (incomingByte[0]>>4) & B00000001;
      Serial.print("Sign: ");
      Serial.println(rc_sign[0], DEC); // Imprime o byte em si.

      rc_vel[0]  = incomingByte[0] & B00001111;
      Serial.print("PWM: ");
      Serial.println(rc_vel[0], DEC); // Imprime o byte em si.  
      Serial.println(pesquisa_vel[rc_vel[0]],DEC);    
   }
      else Serial.println("Nao e este robo");

//segundo byte
      Serial.print("And: ");
      Serial.println(incomingByte[1], BIN); // Imprime o byte em si.
      rc_robo[1]  = (incomingByte[1]>>6) & B00000011;
      Serial.print("Robo: ");
      Serial.println(rc_robo[1], DEC);
   
      // Tratando o Byte recebido
      if (rc_robo[1]==this_robot){
        
      rc_roda[1] = (incomingByte[1]>>5) & B00000001;
      Serial.print("Roda: ");
      Serial.println(rc_roda[1], DEC); // Imprime o byte em si.
        
      rc_sign[1] = (incomingByte[1]>>4) & B00000001;
      Serial.print("Sign: ");
      Serial.println(rc_sign[1], DEC); // Imprime o byte em si.

      rc_vel[1]  = incomingByte[1] & B00001111;
      Serial.print("PWM: ");
      Serial.println(rc_vel[1], DEC); // Imprime o byte em si.  
      Serial.println(pesquisa_vel[rc_vel[1]],DEC);       
  
    }
      else Serial.println("Nao e este robo");
  
 if(rc_robo[0]!=rc_robo[1])
 {
   Serial.println("Robos nao bateram");
 }
 
else if(rc_roda[0]!=0 || rc_roda[1]!=1)
 {
   Serial.println("Rodas nao bateram");
 }
 
else {
        refEsq=pesquisa_vel[rc_vel[0]]; //atualiza referencia roda esquerda
        //pwmEsq=pwm_inicial[rc_vel[0];//setpoint pwm inicial
        cponte(mEsq1, mEsq2, 0);//atualiza valores da Ponte H
  
        refDir=pesquisa_vel[rc_vel[1]];
        //pwmDir=pwm_inicial[rc_vel[1]sign];//setpoint pwm inicial
        cponte(mDir1,mDir2, 1); 

     }
 
   }//leitura
 }//loop
