#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
int val = 0;
unsigned long previousMillis = 0;    
const long interval = 10000;         

void setup() {
  Serial.begin(115200);
  SerialBT.begin("MYESP32");
  Serial.println("The device started, now you can pair it with bluetooth!");
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    val = hallRead();
    SerialBT.print("Hall effect sensor value: ");
    SerialBT.println(val);  
  }
}
