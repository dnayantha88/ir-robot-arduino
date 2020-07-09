#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library
#include <IRremote.h>

//our L298N control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 4;
const int RightMotorBackward = 5;

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function

int RECV_PIN =11;        //pin 11 of arduino to data pin of ir receiver
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  distance = readPing();
  delay(100);
}

void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);

  if (distance <= 20){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
  }
  else{
    if (irrecv.decode(&results))
    {
     Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
    }
   //bot moves front
    if(results.value==0xFFC03F)
    {
      digitalWrite(LeftMotorBackward,LOW);
      digitalWrite(LeftMotorForward,HIGH);
      digitalWrite(RightMotorBackward,HIGH);
      digitalWrite(RightMotorForward,LOW);
    }
    //bot moves back
    if(results.value==0xFF7A85)
    {
      digitalWrite(LeftMotorBackward,HIGH);
      digitalWrite(LeftMotorForward,LOW);
      digitalWrite(RightMotorBackward,LOW);
      digitalWrite(RightMotorForward,HIGH);
    }
    //bot moves left
     if(results.value==0xFF02FD)
    {
      digitalWrite(LeftMotorBackward,LOW);
      digitalWrite(LeftMotorForward,HIGH);
      digitalWrite(RightMotorBackward,HIGH);
      digitalWrite(RightMotorForward,HIGH);
    }
    //bot moves right
     if(results.value==0xFF40BF)
    {
      digitalWrite(LeftMotorBackward,HIGH);
      digitalWrite(LeftMotorForward,HIGH);
      digitalWrite(RightMotorBackward,HIGH);
      digitalWrite(RightMotorForward,LOW);
    }
    //bot stops
    if(results.value==0xFFFA05)
    {
      digitalWrite(LeftMotorBackward,HIGH);
      digitalWrite(LeftMotorForward,HIGH);
      digitalWrite(RightMotorBackward,HIGH);
      digitalWrite(RightMotorForward,HIGH);
    } 
  }
    distance = readPing();
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm==0){
    cm=250;
  }
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveBackward(){

  goesForward=false;

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
}



