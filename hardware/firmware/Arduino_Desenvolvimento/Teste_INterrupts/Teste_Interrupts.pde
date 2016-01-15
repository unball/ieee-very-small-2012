  const int motorCPin = 13;    // H-bridge leg 1 (pin 5)
  const int motorDPin = 12;    // H-bridge leg 2 (pin 7)
  const int enablePin = 10;    // H-bridge enable pin PWM
  const int ledPin = 13;      // LED 
  const float pi=3.14159265;
  volatile unsigned long contador=0;
  volatile int flag_n_sat=1;
  float vref;
  float vinst;
  float erro0=0, erro1=0, tensao0=0, tensao1=0;

  void setup() {
   // interrupts();
    Serial.begin(9600);
    Serial.write("Iniciando");   
    
    // set all the other pins you're using as outputs:
    pinMode(motorCPin, OUTPUT); 
    pinMode(motorDPin, OUTPUT); 
    pinMode(enablePin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    vref=2000;
  
    blink(ledPin, 3, 100);
  }

  void loop() {
    
    encoder();
  }
   
void encoder(){
contador=0;
attachInterrupt(0, soma, RISING);//digital pin 2
delay(1);
detachInterrupt(0);
contador=contador-2
vinst=contador/512.0*1000.0*60.0;
Serial.write("Contador=");
Serial.println(contador);
//Serial.write("Velocidade atual=");
//Serial.println(vinst);
} 
 


void soma(){
contador++;
}



void blink(int whatPin, int howManyTimes, int milliSecs) {//pisca led
    int i = 0;
    for ( i = 0; i < howManyTimes; i++) {
      digitalWrite(whatPin, HIGH);
      delay(milliSecs/2);
      digitalWrite(whatPin, LOW);
      delay(milliSecs/2);
    }
  }
