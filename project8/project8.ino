#include <WiFi.h>
#include "ESP32_MailClient.h"
const char* ssid = "####";
const char* password = "#####";

#define emailSenderAccount    "#####@gmail.com"
#define emailSenderPassword   "#####"
#define emailRecipient        "######"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 Gas Leakage Alert for your kitchen"
 
// Callback function to get the Email sending status
void sendCallback(SendStatus info);
String lastgaslevel;
unsigned long previousMillis = 0;
unsigned long interval = 5000;
SMTPData smtpData;
void setup(){
  Serial.begin(115200);
  Serial.println();
 
  Serial.print("Connecting");
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
 
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.println();
  Serial.println("Preparing to send email");
  Serial.println();
}
void loop() {
   unsigned long currentMillis = millis();
   if (currentMillis - previousMillis >= interval) {
	previousMillis = currentMillis;
    float gas_analog_value = analogRead(35);
    float gas_value = ((gas_analog_value/4095)*100);
	if(gas_value>= 0){
    sendEmail();
    delay(5000);
	}
  } 
}
 
void sendEmail(){
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
 
  // Set the sender name and Email
  smtpData.setSender("ESP32", emailSenderAccount);
 
  // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("High");
 
  // Set the subject
  smtpData.setSubject(emailSubject);
 
  // Set the message with HTML format
  smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Gas Leakage detected! Please check your kitchen right now to stop the leakage!!!</h1><p>- Sent from ESP32 board</p></div>", true);
 
  // Add recipients, you can add more than one recipient
  smtpData.addRecipient(emailRecipient);
  smtpData.setSendCallback(sendCallback);
 
  //Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
 
  //Clear all data from Email object to free memory
  smtpData.empty();
}
 
// Callback function to get the Email sending status
void sendCallback(SendStatus msg) {
  // Print the current status
  Serial.println(msg.info());
 
  // Do something when complete
  if (msg.success()) {
    Serial.println("----------------");
  }
}
