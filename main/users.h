#include <HTTPClient.h>
#include <Arduino_JSON.h>
String serverName = "http://" + local_pc_ip + ":" + local_pc_port + "/api/users/randomUser";
String u[0];

String getUsers() {
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(serverName);
  Serial.print(serverName );
  http.addHeader("Content-Type", "application/json");   

  // Data to send with HTTP POST
  // Send HTTP POST request
  int httpResponseCode = http.POST("{\"pulse\":\"200\"}");
  String payload = "{}";

  if (httpResponseCode > 0) {
    Serial.println("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
    Serial.println(payload);
    //users = [payload];
    //Serial.println(users);
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
