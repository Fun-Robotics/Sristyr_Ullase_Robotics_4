void setup() {
  Serial.begin(115200);
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
  delay(2000);
}

void loop() {
  Serial.print("loop() running on core ");
  Serial.println(xPortGetCoreID());
  delay(2000);
}