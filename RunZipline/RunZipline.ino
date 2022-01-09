#include <AverageFilter.h>

#define FILTER_LEN 5
#define FILTER_THRESHOLD 300
AverageFilter forwardSensor = AverageFilter(A0, FILTER_LEN, FILTER_THRESHOLD, true);
AverageFilter backwardSensor = AverageFilter(A1, FILTER_LEN, FILTER_THRESHOLD, true);

#define MOTOR_PIN 5
#define FORWARD_SPEED 20
#define BACKWARD_SPEED 0
#define STOPPED_SPEED 0
boolean goingForward = true;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, FORWARD_SPEED);
  goingForward = true;
  delay(200);
  analogWrite(MOTOR_PIN, 0);
  
  Serial.begin(9600);
  Serial.println("Setup done.");
}

void loop() {
  forwardSensor.update();
  backwardSensor.update();
  boolean forwardOut = forwardSensor.output();
  boolean backwardOut = backwardSensor.output();
  if (goingForward && forwardOut) {
    analogWrite(MOTOR_PIN, BACKWARD_SPEED);
    Serial.println("Going backwards");
    goingForward = false;
  } else if (!goingForward && backwardOut) {
    analogWrite(MOTOR_PIN, FORWARD_SPEED);
    Serial.println("Going forwards");
    goingForward = true;
  }
  delay(200);
}
