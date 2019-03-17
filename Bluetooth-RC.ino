  #include <Servo.h>

#include <SoftwareSerial.h>
#define TIMEOUT 100

SoftwareSerial BTSerial(1, 0); // RX, TX
 int state = 0;        // for incoming serial data
 long startTime = millis();

//motor 1
int enA = 10;
int in1 = 9;
int in2 = 8;

//motor 2
int enB = 4;
int in3 = 6;
int in4 = 5;
Servo myservo;

int pos = 0;

void setup() {
pinMode(enA,OUTPUT);
pinMode(enB,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);








 BTSerial.begin(9600);
 pinMode(13,OUTPUT);
  myservo.attach(2);
}

void loop() {

if(BTSerial.available() > 0){    // condition when you receive data:
   state = BTSerial.read();       // state = read the incoming data
   startTime = millis();
  
   if (state == '0') {              //if data received equal to '0', LED OFF

     BTSerial.println("LED: off");
   }

 
   else if (state == '1') {        //if data received equal to '1', LED ON

     BTSerial.println("LED: on");
   }

   else if ( state == 'p'){
    pedang();
    }
   
   else if (state == 'F') {        //if data received equal to 'w', MOVE FORWARD
     Forward();
     BTSerial.println("MOVE: forward");
   }
   
   else if (state == 'B') {        //if data received equal to 's', MOVE BACKWARD
    Reverse();
     BTSerial.println("MOVE: backward");
   }

   else if (state == 'L') {        //if data received equal to 'a', ROTATE LEFT
     Left();
     BTSerial.println("ROTATE: left");
   }

   else if (state == 'R') {        //if data received equal to 'd', ROTATE RIGHT
     Right();
     BTSerial.println("ROTATE: right");
   }
 }


 else if((millis() - startTime) >= TIMEOUT){    //if there is no data receive within 0.1 sec, motor stop
   Stop();
 }
 

  /*to counter robot from jerk, uncomment the firstline and the all lines that have 'millis()' and disable the last 'else' condition*/ 
}





void Left() {

// turn on motor A
digitalWrite(in1,1);
digitalWrite(in2,0);
analogWrite(enA,200);

//turn on motor B
digitalWrite(in3,1);
digitalWrite(in4,0);
analogWrite(enB,200);


}

void Stop()
{

analogWrite(enA,0);
analogWrite(enB,0);

}

void Forward()
{
// turn on motor A
digitalWrite(in1,0);
digitalWrite(in2,0);
analogWrite(enA,250);

//turn on motor B
digitalWrite(in3,0);
digitalWrite(in4,0);
analogWrite(enB,250);

}

void Reverse()
{
// turn on motor A
digitalWrite(in1,1);
digitalWrite(in2,1);
analogWrite(enA,210);

//turn on motor B
digitalWrite(in3,1);
digitalWrite(in4,1);
analogWrite(enB,210);

}

void Right() {

// turn on motor A
digitalWrite(in1,0);
digitalWrite(in2,0);
analogWrite(enA,200);

//turn on motor B
digitalWrite(in3,0);
digitalWrite(in4,0);
analogWrite(enB,200);


}
void pedang() {
  for (pos = 0; pos <= 180; pos +=5){
  myservo.write(pos);
  delay(15);
}

for (pos =180;pos >=0; pos -=5){
  myservo.write(pos); 
  delay(15);
}

}

