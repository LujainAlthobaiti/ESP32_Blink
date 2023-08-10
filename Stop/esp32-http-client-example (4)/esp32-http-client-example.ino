#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const String url = "https://s-m.com.sa/s.html";

#define Stop 12 //Red
#define Left 14 //purple
#define Right 25 //Pink
#define Backward 33 //orange
#define Forward 32 //yellow

String payload = "";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(Stop, OUTPUT);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");

}

void loop() {

  HTTPClient http;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println();
    Serial.println(payload);

    if( payload == "stop"){
      digitalWrite(Stop, HIGH);
    }
    else{
      digitalWrite(Stop, LOW);
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    Serial.println(":-(");
  }
}