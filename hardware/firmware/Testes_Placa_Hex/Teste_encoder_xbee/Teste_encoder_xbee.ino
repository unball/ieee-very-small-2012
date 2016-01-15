int flagR=0 ,flagL=0;
unsigned int contadorL=0, contadorR=0;

  void setup() {
Serial.begin(9600);
    interrupts();
pinMode(2,INPUT);
digitalWrite(2,HIGH);
pinMode(3,INPUT);
digitalWrite(3,HIGH);
attachInterrupt(0, somaL, RISING);//digital pin 2-avr4
attachInterrupt(1, somaR, RISING);//digital pin 3-avr5
pinMode(A5,OUTPUT);
  }

  void loop() {
Serial.print("ContadorR= ");
Serial.println(contadorR);
Serial.print("ContadorL= ");
Serial.println(contadorL);
 delay(1000);
}

void somaR(){
contadorR++;
}

void somaL(){
contadorL++;
}
