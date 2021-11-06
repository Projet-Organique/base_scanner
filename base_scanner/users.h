#include <HTTPClient.h>
#include <Arduino_JSON.h>
String serverName = "http://" + local_pc_ip + ":" + local_pc_port + "/api/users/randomUser";


String updateUser(String id, String pulseValue){
  HTTPClient http;

// Your IP address with path or Domain name with URL path
http.begin(serverName + id);
Serial.print(serverName + id);
  http.addHeader("Content-Type", "application/json");  
// Send HTTP POST request
String json = "{\"onReceiver\":\"" + String(reveiverValue) + "\"}";
int httpResponseCode = http.PUT(json);

String payload = "{}";

if (httpResponseCode > 0) {
  Serial.println("HTTP Response code: ");
  Serial.println(httpResponseCode);
  payload = http.getString();
  Serial.println(payload); 
}
else {
  Serial.print("Error code: ");
  Serial.println(httpResponseCode);
}
// Free resources
http.end();

return payload;

}

