#include <SoftwareSerial.h>


int rear1_f = 2;
int rear1_b = 3;
int rear2_f = 4;
int rear2_b = 5;

SoftwareSerial car2(6,7); //RX TX

void setup()
{
	pinMode(rear1_f,OUTPUT);
	pinMode(rear1_b,OUTPUT);
	pinMode(rear2_f,OUTPUT);
	pinMode(rear2_b,OUTPUT);
	Serial.begin(9600);
}

void loop()
{
	char a = car2.read();

	 if(car2.available())
	{
		
		if(a==0) pause();
 		if(a==1) forward(100);
		if(a==2) right(100);
		if(a==3) left(100);

	// when the cars reach at the intersection the must be programmed to turn around
	// car 1 code to reach the destination. this must be fired accordingly //check goto and interrupts in arduino 
	if (a==4)
	{
		right(1000);
		forward(1000);
		car2.write(20);      // telling the server the carhas successful in going past the intersection 
	}

	if(a==5)
	{
		forward(100000);
	}
	}
	 
}
void forward(int t)
{
	digitalWrite(rear1_f,HIGH);
	digitalWrite(rear1_b,LOW);
	digitalWrite(rear2_f,HIGH);
	digitalWrite(rear2_b,LOW);
	delay(t);
	digitalWrite(rear1_f,LOW);
	digitalWrite(rear1_b,LOW);
	digitalWrite(rear2_f,LOW);
	digitalWrite(rear2_b,LOW);

}

void right(int t)
{
	digitalWrite(rear1_f,HIGH);
	digitalWrite(rear1_b,LOW);
	digitalWrite(rear2_f,HIGH);
	digitalWrite(rear2_b,LOW);
	delay(t);
	digitalWrite(rear1_f,LOW);
	digitalWrite(rear1_b,LOW);
	digitalWrite(rear2_f,LOW);
	digitalWrite(rear2_b,LOW);

}

void left(int t)
{
	digitalWrite(rear1_f,LOW);
	digitalWrite(rear1_b,HIGH);
	digitalWrite(rear2_f,LOW);
	digitalWrite(rear2_b,HIGH);
	delay(t);
	digitalWrite(rear1_f,LOW);
	digitalWrite(rear1_b,LOW);
	digitalWrite(rear2_f,LOW);
	digitalWrite(rear2_b,LOW);

}

void pause()
{
  digitalWrite(rear1_f,LOW);
  digitalWrite(rear1_b,LOW);
  digitalWrite(rear2_f,LOW);
  digitalWrite(rear2_b,LOW);  
}
