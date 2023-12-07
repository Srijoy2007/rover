#include <Servo.h>

#define trigPin 10
#define echoPin 13

int in1 = 2;
int in2 = 3;
int enA = 4;

int in3 = 5;
int in4 = 7;
int enB = 6;

bool movingForward = false;  // Declare a boolean variable to store the state of motion

Servo myServo;  

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  myServo.attach(9);  // Attach the servo to pin 9
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 100);
  analogWrite(enB, 100);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  // Measure distance 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration / 2) * 0.0343;

  // Motor control based 
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'w':
        movingForward = true;
        break;
      case 's':
        movingForward = false;
        break;
    }
  }

  // Motor control based on distance
  if (distance < 6.0) {
    stopMotors();
    myServo.write(90);  
  } else {
    if (movingForward) {
      moveForward();
      myServo.write(180); 
    } else {
      stopMotors();
      myServo.write(90);  
    }
  }

  delay(100); 
}

