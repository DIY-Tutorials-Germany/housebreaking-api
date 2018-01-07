/*
 * erstellt von DIY Tutorials Germany
 * Einbruch Pushalarm via Phushingbox API
 * gemacht für ESP-8266 12 
 */
 
#include <ESP8266WiFi.h>
/*
 * Folgend muss Wlan SSID und Passwort verändert werden.
 */
//WLAN
const char* MY_SSID = "WLAN-12345"; //WLan SSID
const char* MY_PWD =  "12345678"; //WLAN Passwort
//Pushingbox API dienst
const char WEBSITEapi[] = "api.pushingbox.com"; //pushingbox API Server
const String devid = "v999998888FEF8"; //"device ID" aus Pushingbox 

#define pin1 D1
int var = 0;


 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(pin1, INPUT_PULLUP);
  digitalWrite (pin1, 0);

  // Aufbau der Wlan-Verbindung
  Serial.print("Connecting to "+*MY_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(MY_SSID, MY_PWD);
  Serial.println("going into wl connect");

  while (WiFi.status() != WL_CONNECTED) //Wlan nicht verbunden warten auf Verbindung
    {
      delay(1000);
      Serial.print(".");
    }
  Serial.println("wifi connected");
  Serial.println("");  
}

 
void loop() {
  delay(500);
  var = digitalRead(pin1);
  

  while (var == 0) {
    delay(100);
    var = digitalRead(pin1);
  }
  //send funktion
  Serial.println(digitalRead(pin1));

   //Verbindung mit API Dienst herstellen
  WiFiClient client;
    Serial.println("Alarm - Fenster wurde geöffnet");
    if (client.connect(WEBSITEapi, 80))
      { 
      client.print("GET /pushingbox?devid=" + devid);
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITEapi);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
      }
  while (var != 0) {
    delay(100);
    var = digitalRead(pin1);
  }
  Serial.println(digitalRead(pin1));   
}
