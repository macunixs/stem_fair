#include <Servo.h>

// L298N to Arduino Nano pin
#define ENA 11
#define in1 10
#define in2 9
#define in3 8
#define in4 7
#define ENB 6

char data = 0;            //Variable for storing received data
int open_repeated = false;
int close_repeated = false;
Servo servoR;  // create servo object to control a servo
Servo servoL;  // create servo object to control a servo

int posR = 0;    // variable to store the servo position
int posL = 0;    // variable to store the servo position

void setup() {
  // put your setup code here, to run once:


    pinMode(ENA,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(in3,OUTPUT);
    pinMode(in4,OUTPUT);
    pinMode(ENB,OUTPUT);
    Serial.begin(9600);
    servoR.attach(3);
    servoL.attach(5);
    servoR.writeMicroseconds(1500);  // set servo to mid-point
    servoL.writeMicroseconds(1500);  // set servo to mid-point

}


void moveForward(){
    digitalWrite(ENA,HIGH);
    
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    
    digitalWrite(ENB,HIGH);
  
  }

  void moveBackward(){
    digitalWrite(ENA,HIGH);
    
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    
    digitalWrite(ENB,HIGH);
  
  }
  
  void turnRight(){
    digitalWrite(ENA,HIGH);
    
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    
    digitalWrite(ENB,HIGH);
  
  }

    void turnLeft(){
    digitalWrite(ENA,HIGH);
    
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    
    digitalWrite(ENB,HIGH);
  
  }

void stopRobot(){
     digitalWrite(ENA,LOW);
     digitalWrite(ENB,LOW);
  }

//servo is at mid position at 90 degree
void servoRclose(){

servoR.attach(3);
servoL.attach(5);

for(posR=90; posR <=150 ; posR+=1){
//    Serial.print("posR: ");
//    Serial.print(posR);
//    Serial.print("      posL: ");
//    Serial.println(posL);
    servoR.write(posR);
    posL = 180-posR;
    servoL.write(posL);

    delay(5);


    }
servoR.detach();
servoL.detach();

}

void servoRopen(){
servoR.attach(3);
servoL.attach(5);
for(posR=150; posR >=90 ; posR-=1){
    servoR.write(posR);
    posL = 180-posR;
    servoL.write(posL);

    delay(5);
//    Serial.print("posR: ");
//    Serial.print(posR);
//    Serial.print("      posL: ");
//    Serial.println(posL);

    }
servoR.detach();
servoL.detach();
}

void watch_dog(){
  Serial.print("time out in 2 sec");
  delay(1000);
  stopRobot();
  }

void loop() {
  
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");   
           
if(data == 'u') {             
moveForward();
}
else if(data == 'd') {        
moveBackward();
}
else if(data == 'r') {        
turnRight();
}
else if(data == 'l') {        
turnLeft();
}

else if(data == 't') {        
stopRobot();
}

else if(data == '1' && close_repeated==false) {
close_repeated = true;
open_repeated = false;
servoRclose();
}

else if(data == '0' && open_repeated==false) {   
close_repeated = false;
open_repeated = true;
servoRopen();
}

else{
digitalWrite(13,LOW);
}
}
Serial.print("open pressed twice?:");
Serial.print(open_repeated);
Serial.print("          close pressed twice?:");
Serial.println(close_repeated);
delay(5);

}
