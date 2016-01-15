int flagR=0 ,flagL=0;
unsigned int contadorL=0, contadorR=0;

  void setup() {
    interrupts();
pinMode(2,INPUT);
digitalWrite(2,HIGH);
pinMode(3,INPUT);
digitalWrite(3,HIGH);
attachInterrupt(0, somaL, RISING);//digital pin 2-avr4
attachInterrupt(1, somaR, RISING);//digital pin 3-avr5
pinMode(A5,OUTPUT);
pinMode(0,OUTPUT);
  }

  void loop() {

if(contadorR>=9728){
contadorR=0;
  if (flagR==1){
digitalWrite(0,HIGH);
flagR=0;}
else{ digitalWrite(0,LOW);
flagR=1;}
}

if(contadorL>=9728){
contadorL=0;
  if (flagL==1){
digitalWrite(A5,HIGH);
flagL=0;}
else{ digitalWrite(A5,LOW);
flagL=1;}
}  
}

void somaR(){
contadorR++;
}

void somaL(){
contadorL++;
}
