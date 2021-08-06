// Program to deal with two inputs 
// using the external interrupt pins

// Input 1 - PIR sensor in pin 2
const int pirPin = 2;  
const int led1_Pin = 13; // Built-in LED
int led1_State = LOW;

// Input 2 - Button in pin 3
const int buttonPin = 3;
const int led2_Pin = 12;
int led2_State = LOW;

void setup()
{
  pinMode(pirPin, INPUT);
  pinMode(led1_Pin, OUTPUT);
  
  pinMode(buttonPin, INPUT);
  pinMode(led2_Pin, OUTPUT);
  
  Serial.begin(9600);
  
  // Enable interrupt 0 for PIR sensor in pin 2
  // Go to the interrupt service routine when pin state changes
  attachInterrupt(digitalPinToInterrupt(pirPin), pir_ISR, CHANGE);
  
  // Enable interrupt 1 for Button in pin 3
  // Go to the interrupt service routine when pin state changes from low to high
  attachInterrupt(digitalPinToInterrupt(buttonPin), button_ISR, RISING);
}

// Interrupt service routine for interrupt 0
void pir_ISR()
{
  // Change LED state when there is a change in PIR state
  led1_State = !led1_State;
  digitalWrite(led1_Pin, led1_State);
  Serial.print("\nPIR State Changed to: ");
  Serial.print(led1_State);
  Serial.print("; LED 1 State is set to: ");
  Serial.print(led1_State);
}

// Interrupt service routine for interrupt 1
void button_ISR()
{
  // Change LED state when button is pressed
  led2_State = !led2_State;
  digitalWrite(led2_Pin, led2_State);
  Serial.print("\nButton is pressed");
  Serial.print("; LED 2 State is set to: ");
  Serial.print(led2_State);
}

void loop()
{
  
}
