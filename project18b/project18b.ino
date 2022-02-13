const int led = 2;  
int val = 0;
void setup() {
  Serial.begin(115200); 
  pinMode(led, OUTPUT);
xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, NULL,  1); 
  delay(500); 
xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, NULL,  0); 
    delay(500); 
}
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(300);
  } 
}
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
val = hallRead();
  // print the results to the serial monitor:
  //Serial.print("sensor = ");
  Serial.println(val);
  }
    delay(30000);
  }
void loop() {
}