// Program to deal with multiple inputs 
// using the internal interrupt pins
// And set timer to make the built-in LED blink

// Input 1 - PIR sensor in pin 2
const int pir1_Pin = 2;  
const int led1_Pin = 8;
int pir1_State = LOW;
int led1_State = LOW;

// Input 2 - PIR sensor in pin 3
const int pir2_Pin = 3;  
const int led2_Pin = 11;
int pir2_State = LOW;
int led2_State = LOW;

// Input 3 - Button in pin 4
const int button_Pin = 5;
const int led3_Pin = 12;
int button_State = LOW;
int led3_State = LOW;

// Built-in LED for Timer
const int timer_led = 13;

void setup()
{
  // Initialize Input and Output Pins
  pinMode(pir1_Pin, INPUT);
  pinMode(led1_Pin, OUTPUT);
  
  pinMode(pir2_Pin, INPUT);
  pinMode(led2_Pin, OUTPUT);
  
  pinMode(button_Pin, INPUT);
  pinMode(led3_Pin, OUTPUT);
  
  pinMode(timer_led, OUTPUT);
  
  Serial.begin(9600);
  
  // Enable interrupts on pins 2,3 and 5
  PCICR |= B00000100;
  PCMSK2 |= B00101100;
  
  // Start Timer
  // Seconds value should be greater than zero.
  float seconds = 4;
  int timer_set = startTimer(1/seconds);
  // Check if timer is set successfully
  if(timer_set == 0)
    Serial.print("\nTimer set successfully.");
  else
    Serial.print("\nTimer not set.");
}

// Function to start timer
int startTimer(double timerFrequency)
{
  noInterrupts();

  double prescaler;
  int compare_reg;
  
  // Do not set timer if timerFrequency is Invalid
  if(timerFrequency <= 0)
  {
    interrupts();
    return -1;
  }
  else
  {
    // Calculate prescaler and OCR1A  
    prescaler = 1024;
    compare_reg = ((16000000 / (prescaler * timerFrequency)) - 1);
    if(compare_reg >= 65536)
    {
        prescaler = 256;
        compare_reg = ((16000000 / (prescaler * timerFrequency)) - 1);
    }
    if(compare_reg >= 65536)
    {
        prescaler = 64;
        compare_reg = ((16000000 / (prescaler * timerFrequency)) - 1);
    }
    if(compare_reg >= 65536)
    {
        prescaler = 8;
        compare_reg = ((16000000 / (prescaler * timerFrequency)) - 1);
    }
    if(compare_reg >= 65536)
    {
        prescaler = 1;
        compare_reg = ((16000000 / (prescaler * timerFrequency)) - 1);
    }
  }
  
  // Do not set timer if timerFrequency is Invalid
  if(compare_reg >= 65536)
  {
    interrupts();
    return -1;
  }
  
  // Clear registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Set OCR1A
  OCR1A = compare_reg;
  
  // Set prescaler 
  if(prescaler == 1) TCCR1B |= (1 << CS10);
  else if (prescaler == 8) TCCR1B |= (1 << CS11);
  else if (prescaler == 64) TCCR1B |= (1 << CS11) | (1 << CS10);
  else if (prescaler == 256) TCCR1B |= (1 << CS12);
  else if (prescaler == 1024) TCCR1B |= (1 << CS12) | (1 << CS10);
  
  // CTC
  TCCR1B |= (1 << WGM12);
    
  // Enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
  return 0;
}

// Interrupt Service Routine for internal interrupts on Port D
ISR(PCINT2_vect) 
{
   if(digitalRead(pir1_Pin) != pir1_State)
   {
     pir1_State = !pir1_State;
     led1_State = !led1_State;
     digitalWrite(led1_Pin, led1_State);
     Serial.print("\nPIR 1 State Changed to ");
  	 Serial.print(pir1_State);
     Serial.print("; LED 1 State is set to ");
     Serial.print(led1_State);
   }
   else if(digitalRead(pir2_Pin) != pir2_State)
   {
     pir2_State = !pir2_State;
     led2_State = !led2_State;
     digitalWrite(led2_Pin, led2_State);
     Serial.print("\nPIR 2 State Changed to ");
  	 Serial.print(pir2_State);
     Serial.print("; LED 2 State is set to ");
     Serial.print(led2_State);
   }
   else if(digitalRead(button_Pin))
   {
     led3_State = !led3_State;
     digitalWrite(led3_Pin, led3_State);
     Serial.print("\nButton pressed");
     Serial.print("; LED 3 State is set to ");
     Serial.print(led3_State);
   }
} 

// Interrupt Service Routine for Timer
ISR(TIMER1_COMPA_vect)
{
  digitalWrite(timer_led, !digitalRead(timer_led));
}

void loop()
{
  
}
