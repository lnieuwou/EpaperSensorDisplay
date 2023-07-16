#include <Arduino.h>
#include "wifiSetup.h"
#include <HTTPClient.h>

#define NODE_RED_SVR "http://192.168.1.29:1880/"

void QueryProbeNames()
{
  HTTPClient http;

  // Change the URL to your Node-RED endpoint
  String url = String(NODE_RED_SVR) + "GetProbeNames";
  http.begin(url);

  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP Response: " + response);
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
}


void setup()
{
  Serial.begin(115200);
  Serial.println("Starting up...");
  delay(2000); // wait for serial to be available

  WifiManagerSetup();

  CheckWifiStatus();
  QueryProbeNames();
}

void loop()
{
  // is configuration portal requested?
  CheckForAndDoWifiConfig();

  // put your main code here, to run repeatedly
  CheckWifiStatus();
}
