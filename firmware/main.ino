// Motor Driver (L298N) pins
const int IN1 = 3, IN2 = 4, ENA = 5;   // Left motor
const int IN3 = 6, IN4 = 7, ENB = 9;   // Right motor

// Ultrasonic Sensors 
// Front sensor
const int trigFront = 8;
const int echoFront = 10;
// Right sensor
const int trigRight = A0;
const int echoRight = A1;
// Left sensor
const int trigLeft = A2;
const int echoLeft = A4;

// Speed tuning (0-255)
int LEFT_PWM  = 180;
int RIGHT_PWM = 160;

// Setup 
void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);

  pinMode(trigFront, OUTPUT); pinMode(echoFront, INPUT);
  pinMode(trigRight, OUTPUT); pinMode(echoRight, INPUT);
  pinMode(trigLeft, OUTPUT);  pinMode(echoLeft, INPUT);

  Serial.begin(9600);
}

// Distance Measurement
long getDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 20000); // timeout 20ms
  if (duration == 0) return 999;              // no echo -> treat as very far
  return duration * 0.034 / 2; // in cm
}

// Motor Movement Functions 
void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // Left forward
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // Right forward
  analogWrite(ENA, LEFT_PWM);
  analogWrite(ENB, RIGHT_PWM);
}

void backward() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right backward
  analogWrite(ENA, LEFT_PWM);
  analogWrite(ENB, RIGHT_PWM);
}

// Pivot turn left
void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);  // Left backward
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);  // Right forward
  analogWrite(ENA, LEFT_PWM);
  analogWrite(ENB, RIGHT_PWM);
}

// Pivot turn right
void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);   // Left forward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);   // Right backward
  analogWrite(ENA, LEFT_PWM);
  analogWrite(ENB, RIGHT_PWM);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

// Main Loop 
void loop() {
  long frontDist = getDistance(trigFront, echoFront);
  long leftDist  = getDistance(trigLeft, echoLeft);
  long rightDist = getDistance(trigRight, echoRight);

  Serial.print("Front: "); Serial.print(frontDist);
  Serial.print(" | Left: "); Serial.print(leftDist);
  Serial.print(" | Right: "); Serial.println(rightDist);

  if (frontDist > 20) {
    forward();   // path free → go straight
  } 
  else {
    stopMotors();
    delay(200);

    if (leftDist > 20) {
      Serial.println("Turning LEFT");
      turnLeft();
      delay(500);   // turn duration
      stopMotors();
      delay(100);
      forward();    // move into the corridor
      delay(300);
    } 
    else if (rightDist > 20) {
      Serial.println("Turning RIGHT");
      turnRight();
      delay(500);
      stopMotors();
      delay(100);
      forward();
      delay(300);
    } 
    else {
      Serial.println("Both sides blocked → BACKWARD");
      backward();
      delay(700);
      stopMotors();
    }
  }
}
