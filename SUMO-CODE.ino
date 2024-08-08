#include <AFMotor.h>  // Include the AFMotor library

// Define motor objects for two DC motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);

// Define pins for ultrasonic sensors
int trigPin1 = 7;
int echoPin1 = 5;
int trigPin2 = A3;
int echoPin2 = A2;

// Define pins for IR sensors
int leftIRPin = A0;
int rightIRPin = A1;
int davomiylik1, davomiylik2, sm1, sm2;
int leftIRValue, rightIRValue;

void plusUltra() {
 
  // Measure distance with first ultrasonic sensor
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin1, LOW);
  davomiylik1 = pulseIn(echoPin1, HIGH);
  sm1 = davomiylik1 / 58;
  Serial.print("Sensor 1 : ");
  Serial.println(sm1);
  delay(200);
 
  // Measure distance with second ultrasonic sensor
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin2, LOW);
  davomiylik2 = pulseIn(echoPin2, HIGH);
  sm2 = davomiylik2 / 58;
  Serial.print("Sensor 2 :");
  Serial.println(sm2);
  delay(200);
}

void readIR() {
 
  // Read values from IR sensors
  leftIRValue = analogRead(leftIRPin);
  rightIRValue = analogRead(rightIRPin);

}

void setup() {
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);

  delay(5000);             // Delay for sensor stabilization

  // Initialize motor speeds and states
  motor1.setSpeed(255);
  motor1.run(RELEASE);
  motor2.setSpeed(255);
  motor2.run(RELEASE);
}

void loop() {
  plusUltra(); // Measure distance with ultrasonic sensors
  readIR();    // Read data from IR sensors

  // Combine ultrasonic and IR sensor data and control robot behavior accordingly
  if ((sm1 < 50 || sm2 < 50) || (leftIRValue < 500 || rightIRValue < 500)) {
    // If obstacle detected by ultrasonic sensor or opponent detected by IR sensors
    // Add your avoidance or attack behavior here
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(300);
    // Add turning behavior to find clear path
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(500);
  } else {
    // If no obstacle or opponent detected
    // Add your normal robot behavior here, e.g., continue searching or patrolling
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(10);
  }
}
