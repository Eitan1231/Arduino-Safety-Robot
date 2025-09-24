//DC Engine
const int motorA1 = 5;
const int motorA2 = 6;
const int motorB1 = 9;
const int motorB2 = 10;

// The first sensor FSR402
int fsrPin1 = A0;
int fsrValue1 = 0;
int fsrThreshold1 = 30;

// The second sensor FSR402
int fsrPin2 = A1;
int fsrValue2 = 0;
int fsrThreshold2 = 30;

int currentSpeed = 90;
//relay with pump air
const int Relaypin = 2;

//Ultrasonic sensor
long duration;
int distance;
const int Trigpin = 11;
const int Echopin = 12;
////HC-06 Bluethooth
//#include <SoftwareSerial.h>
//SoftwareSerial BTSerial (4,3);
void setup() {
  Serial.begin(9600);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(fsrPin1, INPUT);
  pinMode(fsrPin2, INPUT);
  pinMode(Relaypin, OUTPUT);
  pinMode(Trigpin, OUTPUT);
  pinMode(Echopin, INPUT);
}

void loop() {
  digitalWrite(Trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigpin, LOW);
  duration = pulseIn(Echopin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);


  while (distance < 15) {
    analogWrite(motorA1, 0);
    digitalWrite(motorA2, LOW);
    analogWrite(motorB1, 0);
    digitalWrite(motorB2, LOW);
    Serial.println("Motors Stopped due to distance < 15 cm");
    currentSpeed = 50;
    digitalWrite(Relaypin, LOW);
    delay(4000);
    digitalWrite(Trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trigpin, HIGH);    
    delayMicroseconds(10);
    digitalWrite(Trigpin, LOW);
    duration = pulseIn(Echopin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
  }

  fsrValue1 = analogRead(fsrPin1);
  fsrValue2 = analogRead(fsrPin2);

  Serial.print("FSR1 Value: ");
  Serial.println(fsrValue1);
  Serial.print("FSR2 Value: ");
  Serial.println(fsrValue2);

  if (fsrValue1 < fsrThreshold1 && fsrValue2 < fsrThreshold2) {

    digitalWrite(Relaypin, HIGH);

    if (currentSpeed < 170) {
      currentSpeed += 10;
      if (currentSpeed > 170) currentSpeed = 170;
    }

    analogWrite(motorA1, currentSpeed);
    digitalWrite(motorA2, LOW);
    Serial.print("Distance: ");
    Serial.println(distance);
    analogWrite(motorB1, currentSpeed);
    digitalWrite(motorB2, HIGH);

    Serial.print("Current Speed (FSR1 or FSR2): ");
    Serial.println(currentSpeed);

  }
  else {
    analogWrite(motorA1, HIGH);
    digitalWrite(motorA2, LOW);
    analogWrite(motorB1, HIGH);
    digitalWrite(motorB2, LOW);
    Serial.println("Motors Stopped");
    digitalWrite(Relaypin, LOW);
    delay(4000);
    currentSpeed = 50;
  }

  delay(500);
}
