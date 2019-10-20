#include <ESP8266WiFi.h>                                                
#include <FirebaseArduino.h>                                            

#define FIREBASE_HOST "enter your address here"                         // the project name address from firebase id
#define FIREBASE_AUTH "enter your secret code here"                    // the secret key generated from firebase
#define WIFI_SSID "You wifi name to which it is to be connected"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "password of your wifi"                                    //password of wifi ssid

String fireStatus = "";                                                   
String mycmd = "";  
int led = D3; 
int ledd = D8; // for external led
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);      
  pinMode(led, OUTPUT);  
   pinMode(ledd, OUTPUT);               
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       
  Firebase.setString("LED_STATUS", "OFF");                                         
   Firebase.setString("MY_personal_led_status", "OFF"); 
}

void loop() {
  fireStatus = Firebase.getString("LED_STATUS");       
  mycmd = Firebase.getString("MY_personal_led_status");   // get ld status input from firebase
  if (fireStatus == "ON"){                                                        
    Serial.println("Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                                 
    digitalWrite(led, HIGH);                                                        
  } 
   if (mycmd == "ON"){                                                          
    Serial.println("My personal Led Turned ON");                         
    digitalWrite(LED_BUILTIN, LOW);                                                 
    digitalWrite(ledd, HIGH);                                                        
    if (mycmd == "OFF"){                                                  
    Serial.println("My personal Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                             
    digitalWrite(ledd, LOW);                                                         
  }
   if (fireStatus == "OFF") {                                                 
    Serial.println("Led Turned OFF");
    digitalWrite(LED_BUILTIN, HIGH);                                               
    digitalWrite(led, LOW);                                                      
  }
  else {
    Serial.println("Wrong Credential! Please send ON/OFF");
  }
}
