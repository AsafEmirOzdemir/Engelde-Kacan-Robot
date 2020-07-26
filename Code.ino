#include <Servo.h>

Servo myServo;

int Back_Left_Further = 0;
int Back_Left_Back = 1;
int Back_Left_Pwm = 3;
int Back_Left_Speed = 200;

int Back_Right_Further = 2;
int Back_Right_Back = 4;
int Back_Right_Pwm = 5;
int Back_Right_Speed = 200;

int Further_Left_Further = 7;
int Further_Left_Back = 8;
int Further_Left_Pwm = 6;
int Further_Left_Speed = 200;

int Further_Right_Further = 13;
int Further_Right_Back = 12;
int Further_Right_Pwm = 11;
int Further_Right_Speed = 200;

int trig = 10;
int echo = 9;

int sure = 0;
int mesafe = 10000;

unsigned long time;

extern volatile unsigned long timer0_millis;

boolean FurtherC = false;
boolean BackC = false;
boolean RightC = false;
boolean LeftC = false;

int l = 0;
int r = 0; 

void setup()
{
  pinMode(Back_Left_Further, OUTPUT);
  pinMode(Back_Left_Back, OUTPUT);  
  pinMode(Back_Left_Pwm, OUTPUT);
  
  pinMode(Back_Right_Further, OUTPUT);
  pinMode(Back_Right_Back, OUTPUT);  
  pinMode(Back_Right_Pwm, OUTPUT);
  
  pinMode(Further_Right_Further, OUTPUT);
  pinMode(Further_Right_Back, OUTPUT);  
  pinMode(Further_Right_Pwm, OUTPUT);
  
  pinMode(Further_Left_Further, OUTPUT);
  pinMode(Further_Left_Back, OUTPUT);  
  pinMode(Further_Left_Pwm, OUTPUT);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  myServo.attach(A0);
  myServo.write(0);
  
  //Serial.begin(9600);
}

void loop()
{
  digitalWrite(trig, LOW);
  delay(5); 
  digitalWrite(trig, HIGH);
  delay(10); 
  digitalWrite(trig, LOW);
   
  sure = pulseIn(echo, HIGH);
  mesafe = sure / 29.1 / 2;
  
  //Serial.println(mesafe);
 	
  time = millis();
  
  if(time > 500) {
    if(mesafe < 100) {
      if(millis() < 1500) {
      	myServo.write(180);
        l = mesafe;
      }
      else if(millis() > 1500 && millis() < 2500) {
      	myServo.write(0); 
        r = mesafe;
      }
      else {
	  	FurtherC = true;
      }
    } 
    else {
      noInterrupts ();
      
      timer0_millis = 0;
      
      interrupts ();
      
      FurtherC = false; 
      
      Further();
    }
  }
  
  if(FurtherC) {  
    //Serial.println(millis());
    
    if(millis() < 4500) {
	  Back();
    }
    else if(millis() > 4500 && millis() < 7000) {
      if(l > r) {
      	Left();  
      }
      else if(r > l) {
      	Right(); 
      }
    }
    else {
      Stop(); 
    }
  }
  else {
  	Stop(); 
  }
}

void Further() {
  if(millis() < 2000) {
  Back_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Left_Pwm, Back_Left_Speed);  
  digitalWrite(Back_Left_Further, HIGH);
  //  
  Back_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Right_Pwm, Back_Right_Speed);  
  digitalWrite(Back_Right_Further, HIGH);
  //  
  Further_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Left_Pwm, Further_Left_Speed);  
  digitalWrite(Further_Left_Further, HIGH);
  //  
  Further_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Right_Pwm, Further_Right_Speed);  
  digitalWrite(Further_Right_Further, HIGH);
    // 
  }
}

void Back() {
  Back_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Left_Pwm, Back_Left_Speed);  
  digitalWrite(Back_Left_Back, HIGH);
  //  
  Back_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Right_Pwm, Back_Right_Speed);  
  digitalWrite(Back_Right_Back, HIGH);
  //  
  Further_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Left_Pwm, Further_Left_Speed);  
  digitalWrite(Further_Left_Back, HIGH);
  //  
  Further_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Right_Pwm, Further_Right_Speed);  
  digitalWrite(Further_Right_Back, HIGH);
  // 
}

void Left() {
  Back_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Left_Pwm, Back_Left_Speed);  
  digitalWrite(Back_Left_Back, HIGH);
  //  
  Back_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Right_Pwm, Back_Right_Speed);  
  digitalWrite(Back_Right_Further, HIGH);
  //  
  Further_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Left_Pwm, Further_Left_Speed);  
  digitalWrite(Further_Left_Back, HIGH);
  //  
  Further_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Right_Pwm, Further_Right_Speed);  
  digitalWrite(Further_Right_Further, HIGH);
  // 
}

void Right() {
  Back_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Left_Pwm, Back_Left_Speed);  
  digitalWrite(Back_Left_Further, HIGH);
  //  
  Back_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Back_Right_Pwm, Back_Right_Speed);  
  digitalWrite(Back_Right_Back, HIGH);
  //  
  Further_Left_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Left_Pwm, Further_Left_Speed);  
  digitalWrite(Further_Left_Further, HIGH);
  //  
  Further_Right_Speed = map(analogRead(A1), 0, 1023, 0, 255);
  
  analogWrite(Further_Right_Pwm, Further_Right_Speed);  
  digitalWrite(Further_Right_Back, HIGH);
  //
}

void Stop() {
  analogWrite(Back_Left_Pwm, 0);  

  analogWrite(Back_Right_Pwm, 0);  

  analogWrite(Further_Left_Pwm, 0);  

  analogWrite(Further_Right_Pwm, 0); 
}





















