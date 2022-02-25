#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
WiFiClient wificlient;

int led = 14;
 
void setup () {
 
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  WiFi.begin("ssid", "your password");
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
  Serial.println("Connected to WiFi Network");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
    http.begin(wificlient, "http://192.168.69.74:5000/read"); //Specify request destination
 
    int httpCode = http.GET(); //Send the request
 
    if (httpCode > 0) { //Check the returning code
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
      if (String(payload) == "on"){
        digitalWrite(led, HIGH);
      }
      if (String(payload) == "off"){
        digitalWrite(led, LOW);
      }
    }
    else Serial.println("An error ocurred");
 
    http.end();   //Close connection
 
  }
 
  delay(2000);    //Send a request every 2 seconds
 
}
