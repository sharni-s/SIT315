// Program to make LED glow when motion is detected
const int pirPin = 2;  
const int ledPin = 13;
int pirState = LOW;
int ledState = LOW;

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  pirState = digitalRead(pirPin);
  Serial.print("\nPIR State: ");
  Serial.print(pirState);
  
  //LED is set to HIGH if motion is detected
  //Else LED is set to LOW
  //The LED is essentially set to the same state as the PIR sensor
  ledState = pirState;
  digitalWrite(ledPin, ledState);
  Serial.print("\tLED State: ");
  Serial.print(ledState);
}