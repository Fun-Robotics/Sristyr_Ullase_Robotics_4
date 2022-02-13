#include "DHT.h"            
#define DHTTYPE DHT11      
const int DHTPin = 4;      
DHT dht(DHTPin, DHTTYPE); 
float h, t;             
String textMessage;  // Variable to store text message

void setup()
{
  Serial.begin(9600);                      
  /* Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);*/
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // Initialise serial commmunication at 9600 bps on U2UXD serial port
  dht.begin();                             
  pinMode(DHTPin, INPUT);                  
  delay(2000);              
  Serial.println("GSMmodule ready...");  //Print test in Serial Monitor
  Serial2.println("AT\r"); 
  delay(100); // Set delay for 100 ms
    Serial2.println("AT+CMGF=1\r"); // AT command to set module to SMS mode
  delay(100); // Set delay for 100 ms
  Serial2.println("AT+CNMI=2,2,0,0,0\r");// Set module to send SMS data to serial out upon receipt
  delay(100); // Set delay for 100 ms
  Serial2.print("AT+CMGD=1,4\r");//delete all the message in the storage
   delay(2000); // Set delay for 2 seconds
}

void loop()
{
  if (Serial.available() > 0)
    Serial2.write(Serial.read());
  if (Serial2.available() > 0)
    Serial.write(Serial2.read());
  if (Serial2.available() > 0) {
    textMessage = Serial2.readString();
    Serial.print(textMessage);
    delay(10);
  }
  t = dht.readTemperature(); //Temperature in Celsius
  h = dht.readHumidity(); //Humidity
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if (textMessage.indexOf("Status") >= 0) {
    textMessage = "";
    String message1 = "Temperature (Celsius): " + String(t);
    String message2 = " Humidity: " + String(h);
    String message = message1 + message2;
    sendSMS(message);
  }
}

// Function that sends SMS
void sendSMS(String message) {
  Serial2.print("AT+CMGS = \"+ZZZxxxxxxxxx\"\r");
  delay(100);
  // Send the SMS
  Serial2.print(message);
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  Serial2.println((char)26);
  delay(100);
  Serial2.println();
  // Give module time to send SMS
  delay(5000);  
}