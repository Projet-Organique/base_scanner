#include <HTTPClient.h>
#include <Arduino_JSON.h>
String randomUserEndpoint = "http://" + local_pc_ip + ":" + local_pc_port + "/api/users/randomUser";
String updateUserEndpoint = "http://" + local_pc_ip + ":" + local_pc_port + "/api/users/";

int userId;

String getRandomUser() {
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(randomUserEndpoint);
  http.addHeader("Content-Type", "application/json");
  // Send HTTP POST request
  String json = "{\"pulse\":\"" + String(pulse) + "\"}";
  int httpResponseCode = http.POST();

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

String updateUser(String id, String pulseValue) {
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(updateUserEndpoint + id);
  Serial.print(updateUserEndpoint + id);
  http.addHeader("Content-Type", "application/json");
  // Send HTTP POST request
  String json = "{\"pulse\":\"" + String(pulseValue) + "\"}";
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
