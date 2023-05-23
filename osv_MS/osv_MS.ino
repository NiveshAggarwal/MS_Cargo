#include<Server.h>

Servo ser1;
int IrL = 2;
int IrR = 3;

int flipspd = 80;
int rampspd = 150;
int turnspd = 100;

int mLPWM = 5;
int mRPWM = 6;
int m1 = 7;
int m2 = 8;
int m3 = 9;
int m4 = 10;

int LedL = 12;
int LedR = 13;
int FrontLED = 4;

bool dir = true;

void setup() {
  ser1.attach(11);
  Serial.begin(9600);
  ser1.write(0);
  pinMode(IrL, INPUT);
  pinMode(IrR, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(mLPWM, OUTPUT);
  pinMode(mRPWM, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(LedL, OUTPUT);
  pinMode(LedR, OUTPUT);
  pinMode(FrontLED, OUTPUT);

}

void flip(){
  analogWrite(mLPWM, flipspd);
  analogWrite(mRPWM, flipspd);
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);

  for(int i=0; i<3; i++){
    digitalWrite(FrontLED, HIGH);
    digitalWrite(LedL, HIGH);
    digitalWrite(LedR, HIGH);
    delay(500);

    if(digitalRead(IrL) == 1 || digitalRead(IrR) == 0){
      delay(100);
      break;
    }

    digitalWrite(FrontLED, LOW);
    digitalWrite(LedL, LOW);
    digitalWrite(LedR, LOW);
    delay(200);

    if(digitalRead(IrL) == 1 || digitalRead(IrR) == 0){
      delay(100);
      break;
    }
  }
  analogWrite(mLPWM, 0);
  analogWrite(mRPWM, 0);
}

void unloading(){
  ser1.write(0);
  digitalWrite(FrontLED, LOW);
  digitalWrite(LedL, LOW);
  digitalWrite(LedR, LOW);
  for(int i = 0; i<61; i = i+15){
    ser1.write(i);
    digitalWrite(FrontLED, HIGH);
    digitalWrite(LedL, HIGH);
    digitalWrite(LedR, HIGH);
    delay(200);
    digitalWrite(FrontLED, LOW);
    digitalWrite(LedL, LOW);
    digitalWrite(LedR, LOW);
    delay(200);    
  }
  for(int i = 0; i<3; i++){
    ser1.write(20);
    delay(300);
    ser1.write(45);
    delay(300);
  }

  ser1.write(0);
}

void loop() {
  int i1 = digitalRead(IrL);
  int i2 = digitalRead(IrR;

  while(dir){

    if(i1 == 0 && i2 == 0){
      analogWrite(mLPWM, rampspd);
      analogWrite(mLPWM, rampspd);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      digitalWrite(FrontLED, HIGH);
    }
    else if(i1 == 1 && i2 == 0){
      analogWrite(mLPWM, 0);
      analogWrite(mLPWM, turnspd);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      digitalWrite(LedL, HIGH);
      delay(200);
      digitalWrite(LedL, LOW);
    }
    else if(i1 == 0 && i2 == 1){
      analogWrite(mLPWM, turnspd);
      analogWrite(mLPWM, 0);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      digitalWrite(LedR, HIGH);
      delay(200);
      digitalWrite(LedR, LOW);
    }
    else if(i1 == 1 && i2 == 1){
      analogWrite(mLPWM, 0);
      analogWrite(mLPWM, 0);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);

      flip();
      unloading();
      dir = false;
    }    
  }

  while(!dir){
    if(i1 == 0 && i2 == 0){
      analogWrite(mLPWM, rampspd);
      analogWrite(mLPWM, rampspd);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      digitalWrite(FrontLED, HIGH);
      
    }
    else if(i1 == 1 && i2 == 0){
      analogWrite(mLPWM, 0);
      analogWrite(mLPWM, turnspd);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      digitalWrite(LedL, HIGH);
      delay(200);
      digitalWrite(LedL, LOW);
    }
    else if(i1 == 0 && i2 == 1){
      analogWrite(mLPWM, turnspd);
      analogWrite(mLPWM, 0);
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
      digitalWrite(LedR, HIGH);
      delay(200);
      digitalWrite(LedR, LOW);
    }
  }
}
