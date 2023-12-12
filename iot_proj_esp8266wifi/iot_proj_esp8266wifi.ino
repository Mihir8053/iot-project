
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SERVER_IP "192.168.77.56:3000"

#ifndef STASSID
#define STASSID "Mihir"
#define STAPSK "password"
#endif

void setup() {

  Serial.begin(115200);

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
//  Serial.println("");
//  Serial.print("Connected! IP address: ");
//  Serial.println(WiFi.localIP());
}

void loop() {
  String data = "XX";
    while (data[0] != '{' && Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
//      sprintf(json_data, "{\"data\":\"%s\"}", data); 
  }
  Serial.flush();

  // wait for WiFi connection
  if ((WiFi.status() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http;

    // read data
//    static char json_data[1024];
//    String data;
//    if (Serial.available() > 0) {
//      data = Serial.readString();
////      sprintf(json_data, "{\"data\":\"%s\"}", data); 
//    }

    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/arduino-data/");  // HTTP
    http.addHeader("Content-Type", "application/json");

    // start connection and send HTTP header and body
    int httpCode = 0;
    if (data != "XX")
      httpCode = http.POST(data);

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
//      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
//        Serial.println("received payload:\n<<");
//        Serial.println(payload);
//        Serial.println(">>");
      }
    } else {
//      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(1000);
}
