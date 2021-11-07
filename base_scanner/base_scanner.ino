/* BASE_SCANNER */

#include <WiFi.h>
#include "wifi.h"
//#include "user.h"
#include "pulseScan.h"
#include <Arduino_JSON.h>

//create a wifi.h for connection with template
/*
  #ifndef WIFI_H
  #define WIFI_H

  const String local_pc_ip = "IP";
  const String local_pc_port = "PORT";
  const char * ssid = "SSID";
  const char * password = "PASSWORD";

  #endif
*/
// connect to wifi â€“ returns true if successful or false if not
bool ConnectWifi(void)
{
  bool state = true;
  int i = 0;

  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }
  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}

void setup() {
  Serial.begin(115200);
  ConnectWifi();

  pulseInit();
  //getUsers(200);
}

void loop() {
  
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    // Serial.println("data received" + users); 
    //pulseScan();
    //delay(10000);
  }
  // Serial.println(value);
}
