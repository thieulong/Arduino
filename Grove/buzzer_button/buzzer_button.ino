#define BUZZER 5
#define button 4     // connect button to D4
int button_state = 0; 

void setup()
{  
  pinMode(BUZZER, OUTPUT);
  pinMode(button, INPUT);
}

void loop()
{
  button_state = digitalRead(button);
  if (button_state == HIGH){
    tone(BUZZER, 1000); //Set the voltage to high and makes a noise
  }else if(button_state == LOW){
    noTone(BUZZER);//Sets the voltage to low and makes no noise
  }
  delay(50);//Waits for 1000 milliseconds
}
