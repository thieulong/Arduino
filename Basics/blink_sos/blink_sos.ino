void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
/*
void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 3; i++){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);                       
      digitalWrite(LED_BUILTIN, LOW);    
      delay(1000);
  }
  for (int i = 0; i < 3; i++){
      digitalWrite(LED_BUILTIN, HIGH);   
      delay(1000);                      
      digitalWrite(LED_BUILTIN, LOW);    
      delay(1000);
      }
  for (int i = 0; i < 3; i++){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);                       
      digitalWrite(LED_BUILTIN, LOW);    
      delay(1000);
  }
}
*/
void loop() {
  int i = 0;
  while (i < 3){
    i++;
    /*Serial.println(i);*/
    if (i%2==0){
      for (int i = 0; i < 3; i++){
        digitalWrite(LED_BUILTIN, HIGH);   
        delay(1000);                      
        digitalWrite(LED_BUILTIN, LOW);    
        delay(1000);
      }
      Serial.println("O");
    }else{
      for (int i = 0; i < 3; i++){
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);                       
      digitalWrite(LED_BUILTIN, LOW);    
      delay(1000);
      }
      Serial.println("S");
    }
  }
}
