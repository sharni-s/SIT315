// Program to make LED glow when motion is detected (using interrupts)
const int pirPin = 2;  
const int ledPin = 13;
int pirState = LOW;
int ledState = LOW;

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // Enable interrupt 0 which uses pin 2
  // Go to the interrupt service routine when pin state changes
  attachInterrupt(digitalPinToInterrupt(pirPin), pir_ISR, CHANGE);
  
}

void loop()
{
  
}

// Interrupt service routine for interrupt 0
void pir_ISR()
{
  pirState = !pirState;
  // Change LED state when there is a change in PIR state
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  Serial.print("\nPIR State Changed to: ");
  Serial.print(pirState);
  Serial.print("; LED State is set to: ");
  Serial.print(ledState);
}