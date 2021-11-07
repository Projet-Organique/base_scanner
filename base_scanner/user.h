#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <ArduinoJson.h>

String resquest(String endpoint, int request, String query) {
  HTTPClient http;
  int httpResponseCode;

  // Your IP address with path or Domain name with URL path
  http.begin(endpoint);
  http.addHeader("Content-Type", "application/json");

  switch (request) {
    case 0:
      httpResponseCode = http.POST(query);
      break;
    case 1:
      httpResponseCode = http.GET();
      break;
    case 2:
      httpResponseCode = http.PUT(query);
      break;
  }

  // Send HTTP POST request

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

String getRandomUser() {
  String randomUserEndpoint = "http://" + local_pc_ip + ":" + local_pc_port + "/api/users/randomUser";
  return resquest(randomUserEndpoint, 1, "null");
}

String updateUser(String content, String pulseValue) {
 /* StaticJsonDocument<200> doc;
  char Buf[150];
  content.toCharArray(Buf, 150);
  char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  DeserializationError error = deserializeJson(doc, json);
  //JsonObject& root = jsonBuffer.parseObject(json);

 String id = doc["sensor"]; */
  String updateUserEndpoint = "http://" + local_pc_ip + ":" + local_pc_port + "/api/users/";// + id;
  return resquest(updateUserEndpoint, 2,  "{\"pulse\":\"" + String(pulseValue) + "\"}");
}
