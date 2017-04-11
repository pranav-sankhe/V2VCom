//processing code

//processing code

import processing.serial.*;

Serial myPort;  // The serial port
int x=0;
void setup() {
  // List all the available serial ports
  printArray(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);
  size(500,500);
  //size(500,500);
  rectMode(CENTER);
  rect(250,250,500,70);
  rect(250,250,70,500);
  rect(250,250,70,70);
  ellipseMode(CENTER);
  ellipse(250,250,30,30);
 
}

void draw() {
  
  
  // Expand array size to the number of bytes you expect
  byte[] inBuffer = new byte[7];
  while (myPort.available() > 0) {
    inBuffer = myPort.readBytes();
    myPort.readBytes(inBuffer);
    if (inBuffer != null) {
      String myString = new String(inBuffer);
      //println(myString);
   
     if(myString.length() == 8){
        println(myString);
       x = Integer.parseInt(myString.substring(0,2));
       println(x);
       
       fill(0,0,120);// add alpha value : for fading out
       ellipse(250+2.5*x,250,10,10);
       x = Integer.parseInt(myString.substring(2,4));
       println(x);
       
       fill(120,0,0);
       ellipse(250,250+2.5*x,10,10);
       x = Integer.parseInt(myString.substring(4,6));
       println(x);
       
       fill(0,120,0);
       ellipse(250-2.5*x,250,10,10);
       x = Integer.parseInt(myString.substring(6,8));
       println(x);
       
       fill(255);
       ellipse(250,250-2.5*x,10,10);
       
     }
       
    //  println(myString);
      
    
    }
  }
}







Day 12
//car


#include <VirtualWire.h>

const int led_pin1 = 6;
const int led_pin2 = 7;
const int led_pin3 = 8;// change this to 8
const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 11;
//const int transmit_en_pin = 3;
int decision=0;

void setup()
{
  delay(1000);
  Serial.begin(9600);    // Debugging only
  Serial.println("setup");
  pinMode(led_pin, OUTPUT);
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
  pinMode(led_pin3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
   
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
 // vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(4000);     // Bits per sec

  vw_rx_start();    // Start the receiver PLL running
}
void turnLeft(){
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  delay(1000);
}

void turnRight(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,HIGH);
  delay(1000);
 
}

void forward(){
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
 delay(1000);
}

void stopm(){
digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);

}
void loop()
{   
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen)) // Non-blocking
  {
    int i;

      digitalWrite(led_pin, HIGH); // Flash a light to show received good message
    // Message with a good checksum received, print it.
    //Serial.print("Got: ");
    //forward();
    for (i = 0; i < buflen; i++)
    {
      Serial.print(buf[i]);
      Serial.print(' ');
          if(buf[i] == 'a' || buf[i]==1){
            //stopm();
            digitalWrite(led_pin1, HIGH);
            digitalWrite(led_pin2, LOW);
            digitalWrite(led_pin3, LOW);
            decision = 1;
            delay(250);
          }
          else if(buf[i] == 'b' || buf[i]==2 ||buf[i]==49){
            //stopm();
            digitalWrite(led_pin2,HIGH);
            digitalWrite(led_pin1,LOW);
            digitalWrite(led_pin3, LOW);
            decision = 2;
            delay(250);
          }
          else if(buf[i] == 'c' || buf[i]==3){
            //stopm();
            digitalWrite(led_pin2,LOW);
            digitalWrite(led_pin1,LOW);
            digitalWrite(led_pin3,HIGH);
            delay(250);
            decision=3;
          }
          else if(buf[i] == 'd' || buf[i]==4){
            if(decision==1){
              turnRight();
                 stopm();
            
            }
            else if(decision==3){
              turnLeft();
                stopm();
            }
            else{
              forward();
              stopm();
            }
           
          }
          else{
            digitalWrite(led_pin2,LOW);
            digitalWrite(led_pin1,LOW);
            digitalWrite(led_pin3, LOW);
            delay(250);
          }
         
    }
    Serial.println();
      digitalWrite(led_pin, LOW);
  }
}

