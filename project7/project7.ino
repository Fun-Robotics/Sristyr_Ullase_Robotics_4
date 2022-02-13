#include <WiFi.h>        
#include <HTTPClient.h>   

const char* ssid = "#####";             
const char* password =  "#####";   

String apiKey = "#######";              
String phone_number = "+8801#########"; //your mobile number
String url;                            
const int reedSwitch = 4;
/* Holds reedswitch state (1=opened, 0=close) */
bool state;

void  message_to_whatsapp(String message)       
{
  //adding all number, your api key, your message into one complete url
  url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&text=" + urlencode(message)+ "&apikey=" + apiKey;
  Serial.println(url);

  postData(); /* calling postData to run the above-generated url once so that you will receive a message.*/
}

void postData()     /*userDefine function used to call api(POST data) */
{
  int httpCode;     /* variable used to get the responce http code after calling api */
  HTTPClient http;  // Declare object of class HTTPClient
  http.begin(url);  /* begin the HTTPClient object with generated url */
  httpCode = http.POST(url); /* Finaly Post the URL with this function and it will store the http code */
  if (httpCode == 200)      // Check if the responce http code is 200
  {
    Serial.println("Sent ok."); // print message sent ok message
  }
  else                      /* if response HTTP code is not 200 it means there is some error. */
  {
    Serial.println("Error."); // print error message.
  }
  http.end();          // After calling API end the HTTP client object.
}

String urlencode(String str)  // Function used for encoding the url
{
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
      }
      yield();
    }
    return encodedString;
}

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);              
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {  
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to the WiFi network"); 
  pinMode(reedSwitch, INPUT_PULLUP);
}

void loop()
{  
  state= digitalRead(reedSwitch);
  if (state){
      message_to_whatsapp("Alert! Your door has been opened!");
	  delay(5000);
      }
}