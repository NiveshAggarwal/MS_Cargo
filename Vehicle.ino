#include <Servo.h>
Servo sg90;

#define MOTOR1_PWM 0
#define MOTOR1_PLUS 1
#define MOTOR1_MINUS 2

#define MOTOR2_PWM 3
#define MOTOR2_PLUS 4
#define MOTOR2_MINUS 5

#define INFRARED_LEFT 6
#define INFRARED_RIGHT 7
// Note: MOTOR1 --> the Left two (2) motors. MOTOR2 --> the Right two (2) motors. 3 pins to control TWO MOTORS AT ONCE.
// Assumption: White line on black background; white = 0 for IR, black = 1; white track; white horizontal = endline.

void idle (void) {
  digitalWrite (MOTOR1_PLUS, LOW);
  digitalWrite (MOTOR1_MINUS, LOW);
  digitalWrite (MOTOR1_PWM, LOW);

  digitalWrite (MOTOR2_PLUS, LOW);
  digitalWrite (MOTOR2_MINUS, LOW);
  digitalWrite (MOTOR2_PWM, LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode (MOTOR1_PWM, OUTPUT);
  pinMode (MOTOR1_PLUS, OUTPUT);
  pinMode (MOTOR1_MINUS, OUTPUT);

  pinMode (MOTOR2_PWM, OUTPUT);
  pinMode (MOTOR2_PLUS, OUTPUT);
  pinMode (MOTOR2_MINUS, OUTPUT);

  pinMode (INFRARED_LEFT, INPUT);
  pinMode (INFRARED_RIGHT, INPUT);

  Serial.begin (9600);
  idle ();
}

void uTurn () {
  int m1plus, m1minus, m2plus, m2minus, m1pwm, m2pwm;
  
  m1plus = MOTOR1_PLUS;
  m1minus = MOTOR1_MINUS;
  m1pwm = MOTOR1_PWM;

  m2plus = MOTOR2_PLUS;
  m2minus = MOTOR2_MINUS;
  m2pwm = MOTOR2_PWM;

  digitalWrite (m1plus, HIGH);
  digitalWrite (m1minus, LOW);
  digitalWrite (m1pwm, 200);

  digitalWrite (m2plus, LOW);
  digitalWrite (m2minus, HIGH);
  digitalWrite (m2pwm, 200);

  delay (1000);
  // This number should be checked.

  digitalWrite (m1plus, LOW);
  digitalWrite (m1minus, LOW);

  digitalWrite (m2plus, LOW);
  digitalWrite (m2minus, LOW);
}

void servoMove () {
  sg90.attach (9);
  sg90.write(17);
  delay (1000);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
      sg90. write (15);
      delay (50);
      sg90.write (17);
      delay (50);
    }
    delay (1000);
  }

  sg90.detach();
  delay (3000);
  return;
}

void traction (int speed) {
  int m1plus, m1minus, m2plus, m2minus, m1pwm, m2pwm, ir1, ir2;

  if (speed > 255) {
    speed = 255;
  }

  m1plus = MOTOR1_PLUS;
  m1minus = MOTOR1_MINUS;
  m1pwm = MOTOR1_PWM;

  m2plus = MOTOR2_PLUS;
  m2minus = MOTOR2_MINUS;
  m2pwm = MOTOR2_PWM;

  ir1 = digitalRead (INFRARED_LEFT);
  ir2 = digitalRead (INFRARED_RIGHT);

  digitalWrite (m1plus, HIGH);
  digitalWrite (m1minus, LOW);

  digitalWrite (m2plus, HIGH);
  digitalWrite (m2minus, LOW);

  if (ir1 == HIGH) {
    analogWrite (m1pwm, speed);
  }
  else {
    analogWrite (m1pwm, 0);
  }
  if (ir2 == HIGH) {
    analogWrite (m2pwm, speed);
  }
  else {
    analogWrite (m2pwm, 0);
    if (ir1 == LOW) 
    {
      return 0;
    }
  }
  return 1;
}

int main() {
  setup();
  int check = 1, speed = 200;

  while (check == 1) {
    check = traction (speed);
  }

  uTurn ();
  servoMove ();
  check = 1;
  speed = 100;

  while (check == 1) {
    check = traction (speed);
  }

  return 0;
}
