#include <HTTPClient.h>
//#include <Arduino_JSON.h>
#include <ArduinoJson.h>

String resquest(String endpoint, int request, String query) {
  Serial.println(endpoint);
  Serial.println(request);
  Serial.println(query);
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

    Serial.println("payload: " + payload);
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
  Serial.println(content);
  //JsonArray& root = jsonBuffer.parseArray(content);
  //const char* world = root["_id"][0];
  // Serial.println(world);
  StaticJsonDocument<256> doc;
  //DynamicJsonDocument doc(1024);
  deserializeJson(doc, content);
  // Serial.println("doc: " + doc);
  String value = doc["_id"];

  String updateUserEndpoint = "http://" + local_pc_ip + ":" + local_pc_port + "/api/users/" + value + "/scan_data/8081";
  return resquest(updateUserEndpoint, 2,  "{\"pulse\":\"" + String(pulseValue) + "\"}");




  //NOW FIND A WAY TO STOP THE CALL OR RESET
}
