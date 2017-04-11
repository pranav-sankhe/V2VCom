//server code

//Final server code:

/* decision making and transmission*/
/* in void loop*/
#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
//const int receive_pin = 2;
//const int transmit_en_pin = 3;
char decision[2];
//int dist1,dist2,dist3,dist4;
#define trigPin1 6
#define echoPin1 7
#define trigPin2 2
#define echoPin2 3
#define trigPin3 4
#define echoPin3 5
#define trigPin4 8
#define echoPin4 9
long duration, distance, RightSensor,BackSensor,FrontSensor,LeftSensor;
//int decision = 0;
void setup()
{
  // Initialise the IO and ISR
  Serial.begin (9600);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, INPUT);
  vw_set_tx_pin(transmit_pin);
  //vw_set_rx_pin(receive_pin);
  //vw_set_ptt_pin(transmit_en_pin);
  //vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(4000);   // Bits per sec
   pinMode(13, OUTPUT);
}

byte count = 1;

void loop()
{
//  char msg[2] = {'1','0'};
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
SonarSensor(trigPin2, echoPin2);
LeftSensor = distance;
SonarSensor(trigPin3, echoPin3);
FrontSensor = distance;
SonarSensor(trigPin4, echoPin4);
BackSensor = distance;
/*if(LeftSensor<=100 && FrontSensor<=100 && RightSensor<=100 && BackSensor<=100){
Serial.print(LeftSensor);
Serial.print(" ");
Serial.print(FrontSensor);
Serial.print(" ");
Serial.print(RightSensor);
Serial.print(" ");
Serial.println(BackSensor);}*/


 if(LeftSensor>=100){
LeftSensor = 99;
}
 if(FrontSensor>=100){
  FrontSensor = 99;
 }
  if(RightSensor>=100){
LeftSensor = 99;
}
 if(BackSensor>=100){
  FrontSensor = 99;
 }
  if(LeftSensor<=9){
Serial.print(0);
Serial.print(LeftSensor);
}
 if(FrontSensor<=9){
  Serial.print(0);
Serial.print(FrontSensor);
 }
  if(RightSensor<=9){
Serial.print(0);
Serial.print(RightSensor);

}
 if(BackSensor<=9){
  Serial.print(0);
Serial.print(BackSensor);
delay(10);
 
 }
 
 Serial.print(LeftSensor);
 Serial.print(FrontSensor);
 Serial.print(RightSensor);
 Serial.print(BackSensor);
delay(10);
 
  if(LeftSensor<= 5)
{
 decision[0] = 'd';
 decision[1] = 'd';
}
else if(FrontSensor>RightSensor && FrontSensor > BackSensor)
{
  decision[0] = 'a';
  decision[1] = 'a';
}
else if(FrontSensor<RightSensor && RightSensor > BackSensor)
{
   decision[0] = 'b';
  decision[1] = 'b';
}
else
{
   decision[0] = 'c';
  decision[1] = 'c';
}

 
  //msg[6] = count;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)decision, 2);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(1000);
  //count = count + 1;
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}

