/*
 * Teste Serial - Futebol de Robôs
 *
 * By Potato Chips! o/
 *
 */
 
 // Defs
 #define this_robot 00 // diretriz que informa qual o numero de cada robo - cada robo recebera um diferente
 #define pwm_out_0 4 // porta de saida da roda 0
 #define pwm_out_1 5 // porta de saida da roda 1
 
 int pesquisa_pwm[] = {0, 15, 31, 47, 63, 79, 95, 111, 127, 143, 159, 175, 191, 207, 223, 239, 255}; 
 int incomingByte = 0;	// for incoming serial data
 
 // Variaveis de tratamento do byte recebido serialmente
 int rc_num = 0; // variavel para receber para qual robo eh a informacao
 int rc_roda = 0; // Define qual roda do robo ira aplicar o pwm
 int rc_sign = 0; // Sentido da roda escolhida -> 1 é negativo
 int rc_pwm = 0; // pwm recebido
 
 void setup()
 {
   Serial.begin(9600);
   pinMode(pwm_out_0, OUTPUT);
   pinMode(pwm_out_1, OUTPUT);
 }
 
 void loop()
 {
   if(Serial.available() > 0) 
   {
      // read the incoming byte:
      incomingByte = Serial.read();

      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, BIN); // Imprime o byte em si.

      // Tratando o Byte recebido
      rc_pwm  = incomingByte & 0b00001111;
      Serial.print("PWM: ");
      Serial.println(rc_pwm, BIN); // Imprime o byte em si.
      rc_sign = (incomingByte>>4) & 0b00000001;
      Serial.print("Sign: ");
      Serial.println(rc_sign, BIN); // Imprime o byte em si.
      rc_roda = (incomingByte>>5) & 0b00000001;
      Serial.print("Roda: ");
      Serial.println(rc_roda, BIN); // Imprime o byte em si.
      rc_num  = (incomingByte>>6) & 0b00000011;
      Serial.print("Num: ");
      Serial.println(rc_num, BIN); // Imprime o byte em si.
      
//      if(rc_roda == 0)
//        rc_roda = pwm_out_0;
//      else
//        rc_roda = pwm_out_1;
//      
//      if(rc_num == this_robot)
//      {
//        if(rc_sign == 1)
//          analogWrite(rc_roda, -pesquisa_pwm[rc_pwm]);
//        else
//          analogWrite(rc_roda, pesquisa_pwm[rc_pwm]);
//      }
      	
    }
 }

