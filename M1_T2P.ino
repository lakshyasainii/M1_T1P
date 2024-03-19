const int LED_PIN = 13;
const int BUTTON_PIN = 6;
const int PIR_SENSOR_PIN = 2;

volatile bool ledState = LOW;
volatile bool motionDetected = false;
volatile bool buttonPressed = false;

void handleButtonInterrupt() {
  buttonPressed = !buttonPressed;
  
  if (buttonPressed) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    
    if (ledState == HIGH) {
      Serial.println("LED on");
    } else {
      Serial.println("LED off");
    }
  }
}

void handleMotionInterrupt() {
  bool pirSensorValue = digitalRead(PIR_SENSOR_PIN);
  
  if (pirSensorValue == HIGH) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Motion detected!");
    motionDetected = true;
  } else {
    motionDetected = false;
  }
  
  if (!motionDetected && !buttonPressed) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("No motion detected");
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PIR_SENSOR_PIN, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIR_SENSOR_PIN), handleMotionInterrupt, CHANGE);
}

void loop() {}
