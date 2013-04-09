
const int minimum = 10;
const int maximum = 100;

const int sensorPin = 0;
const int ledPin = 9;

void setup() {
}

void loop() {
  int value = analogRead(sensorPin);
  
  value = (value - minimum) * 255 / (maximum - minimum) ;
  
  analogWrite(ledPin, value);
  
  delay(10);
}

