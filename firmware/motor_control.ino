
#include <Servo.h>

// -------------------- Motor Definitions --------------------
#define NUM_SERVOS 5

Servo servos[NUM_SERVOS];
int servoPins[NUM_SERVOS] = {5, 6, 7, 8, 9};

// Stepper motor pins (example)
#define STEP_PIN 2
#define DIR_PIN 3

// -------------------- Sensor Pins --------------------
int tempPins[NUM_SERVOS] = {A0, A1, A2, A3, A4};
int vibPins[NUM_SERVOS]  = {A5, A6, A7, A8, A9};

// -------------------- Variables --------------------
int servoAngles[NUM_SERVOS] = {90, 90, 90, 90, 90};
unsigned long lastSendTime = 0;

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);      // Debug
  Serial1.begin(115200);   // Arduino Mega → ESP32

  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(servoAngles[i]);
  }

  Serial.println("Robotic Arm Controller Initialized");
}

// -------------------- Main Loop --------------------
void loop() {

  // ---- Base Rotation (Stepper) ----
  rotateBase();

  // ---- Servo Control (Manual / Joystick placeholder) ----
  updateServos();

  // ---- Read Sensors ----
  readSensors();

  // ---- Send Data to ESP32 ----
  if (millis() - lastSendTime > 1000) {
    sendDataToESP32();
    lastSendTime = millis();
  }
}

// -------------------- Functions --------------------

void rotateBase() {
  digitalWrite(DIR_PIN, HIGH);
  for (int i = 0; i < 200; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(800);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(800);
  }
}

void updateServos() {
  // Placeholder for joystick / manual control
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(servoAngles[i]);
  }
}

void readSensors() {
  // Sensor reads (unstable during full integration)
  for (int i = 0; i < NUM_SERVOS; i++) {
    int tempVal = analogRead(tempPins[i]);
    int vibVal  = analogRead(vibPins[i]);

    // Currently only read for debugging
  }
}

void sendDataToESP32() {
  Serial1.print("ARM_DATA,");

  for (int i = 0; i < NUM_SERVOS; i++) {
    Serial1.print(servoAngles[i]);
    Serial1.print(",");
  }

  Serial1.println("END");
}
