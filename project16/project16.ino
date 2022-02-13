#define CUSTOM_SETTINGS
#define INCLUDE_MOTORCONTROL_MODULE
#include <DabbleESP32.h>


uint8_t pinServo1 =  4;
uint8_t pinServo2 =  5;
uint8_t pwmMotor1 =  12;
uint8_t dir1Motor1 = 13;
uint8_t dir2Motor1 = 14;
uint8_t pwmMotor2 =  21;
uint8_t dir1Motor2 = 22;
uint8_t dir2Motor2 = 23;

void setup() {
  Serial.begin(115200);         
  Dabble.begin("MyEsp32");     
 //set bluetooth name of your device  
}

void loop() {
  Dabble.processInput();             
/*this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.   */
  /*this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile. */
  Controls.runServo1(pinServo1);
  Controls.runServo2(pinServo2);
  Controls.runMotor1(pwmMotor1,dir1Motor1,dir2Motor1);             
  Controls.runMotor2(pwmMotor2,dir1Motor2,dir2Motor2);             
}
