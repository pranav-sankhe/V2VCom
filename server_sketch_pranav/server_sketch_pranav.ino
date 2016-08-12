#include <SoftwareSerial.h>



int trig1 = 2;
int trig2 = 4;
int trig3 = 6;
int echo1 = 3;
int echo2 = 5;
int echo3 = 7;

//variables for  calculating distances
int distance1[2] ;
long double duration1;
int distance2[2];
long double duration2 = 0;
int distance3[2];
long double duration3 = 0;

//communication pins
SoftwareSerial car1(8,9); //RX TX
SoftwareSerial car2(10,11); //RX TX
SoftwareSerial car3(12,13); //RX TX
char a,b,c ;

//definitions
//0 = stop
//1 = forward 
//2 = right
//3 = left 
//4 = car go past the intersection
//5 = car is past the intesection and then instruct it to continue moving forward
//10 = ask the cars
//20 = telling the server that the car has successful in going past the intersection 
//11 = forward and forward (sent by the car)
//12 = forward and right (sent by the car)
//13 = forward and left	(sent by the car)

void setup() 
{
 Serial.begin(9600);
 pinMode(trig1,OUTPUT);
 pinMode(trig2,OUTPUT);
 pinMode(trig3,OUTPUT);
 pinMode(echo1,INPUT);
 pinMode(echo2,INPUT);
 pinMode(echo3,INPUT);
}

void loop() 
{
 for(int i=0;i<2;i++)              
 {
	digitalWrite(echo1, LOW);   	
	digitalWrite(trig1, LOW);                    
	delayMicroseconds(2);
	digitalWrite(trig1, HIGH);
	delayMicroseconds(10); 
	duration1 =  pulseIn(echo1, HIGH,8000);        //wait for 8 milliseconds else move to next reading
	distance1[i] = (duration1/2)/29.1;                                     
	digitalWrite(trig1, LOW);
	digitalWrite(echo1, LOW);
	if (distance1[i] == 0) distance1[1] = 500;	
        Serial.println(distance1[i]);
	delay(20);                                      //for stability of sensor
 }
for(int i=0;i<2;i++)
 {	                                
	digitalWrite(echo2, LOW);
	digitalWrite(trig2, LOW);                    
	delayMicroseconds(2);
	digitalWrite(trig2, HIGH);
	delayMicroseconds(10); 
	duration2 =  pulseIn(echo2, HIGH,8000);        //wait for 8 milliseconds else move to next reading
	distance2[i] = (duration1/2)/29.1;                                     
	digitalWrite(trig2, LOW);
	digitalWrite(echo2, LOW);
	if (distance2[i] ==0) distance2[0] = 500;
        Serial.println(distance2[i]);	
	delay(20);                                       //for stability of sensor
 }

 for(int i=0;i<2;i++)
  {	 
	digitalWrite(echo3, LOW);
	digitalWrite(trig3, LOW);                    
	delayMicroseconds(2);
	digitalWrite(trig3, HIGH);
	delayMicroseconds(10); 
	duration3 =  pulseIn(echo3, HIGH,8000);        //wait for 8 milliseconds else move to next reading
	distance3[i] = (duration3/2)/29.1;                                     
	digitalWrite(trig3, LOW);
	digitalWrite(echo3, LOW);
	if (distance3[i] ==0) distance3[0] = 500;
        Serial.println(distance3[i]);	
	delay(20);                                       //for stability of sensor
 }

/*
 	// ask the cars about their route
 	// 10 = ask the cars
 	//11 = forward and forward (sent by the car)
 	//12 = forward and right (sent by the car)
 	//13 = forward and left	(sent by the car)
 	car1.write(10);
 	if(car1.available())
 	{
 		char a = car1.read()
 	}

 	car2.write(10);
 	if(car2.available())
 	{
 		char b = car2.read()
 	}

 	car3.write(10);
 	if(car3.available())
 	{
 		char c = car3.read()
 	}
*/

    //

 	if(a==20)
 	{
 		car1.write(5);		//car is past the intesection and then instruct it to continue moving forward
	}

	if(b==20)
 	{
 		car2.write(5);		//car is past the intesection and then instruct it to continue moving forward
	}

	if(c==20)
 	{
 		car3.write(5);		//car is past the intesection and then instruct it to continue moving forward
	}

	

	//ACCIDENT PREVENTION
	if(abs(distance1[0]-distance1[1])>2 && abs(distance2[0]-distance2[1])>2)
	{
	 	
		if(distance1[0] < 10 && distance2[0] < 10)                //if the situation is too urgent
	 	{
                car1.write("0");                                          //instruct the cars to stop
		car2.write("0");										  //instruct the cars to stop
                }

		if(distance1[0] < 25 && distance2[0] < 25)
		{
			car1.write("0");
			car2.write("1");
		}
	}
         
	
	if(abs(distance1[0]-distance1[1])>2 && abs(distance3[0]-distance3[1])>2)
	{
	 	
		if(distance1[0] < 10 && distance3[0] < 10)                //if the situation is too urgent
	 	car1.write("0");                                          //instruct the cars to stop
		car3.write("0");										  //instruct the cars to stop
	
		if(distance1[0] < 25 && distance3[0] < 25)
		{
			car1.write("0");
			car3.write("1");
		}
	}


	if(abs(distance2[0]-distance2[1])>2 && abs(distance3[0]-distance3[1])>2)
	{
	 	
		if(distance2[0] < 10 && distance3[0] < 10)                //if the situation is too urgent
	 	car3.write("0");                                          //instruct the cars to stop
		car2.write("0");										  //instruct the cars to stop
		
		if(distance2[0] < 25 && distance3[0] < 25)
		{
			car3.write("0");
			car2.write("1");

		}

	}
	

	if(abs(distance1[0]-distance1[1])>2 && abs(distance2[0]-distance2[1])>2 && abs(distance1[0]-distance1[1])>2)
	{
	 	
		if(distance1[0] < 10 && distance2[0] < 10)                //if the situation is too urgent
	 	car1.write("0");                                          //instruct the cars to stop
		car2.write("0");										  //instruct the cars to stop
		car3.write("0");										  //instruct the cars to stop
	

	}
	
	//TRAFFIC MANAGEMENT
//predefined routes for cars
//car 1 = forward + left 
//car 2 = forward + right 
//car 3 = forward + right




// when the cars reach at the intersection the must be programmed to turn around
	// car 1 code to reach the destination. this must be fired accordingly //check goto and interrupts in arduino 
	if (distance1[0]<5)
	{
		car1.write("4");
	}

	// car 2 code to reach the destination. this must be fired accordingly
	if (distance1[0]<5)
	{
		car2.write("4");                                                                                     	
	}
	
	// car 3 code to reach the destination. this must be fired accordingly
	if (distance1[0]<5)
	{
		car3.write("4");
	}


	
}


