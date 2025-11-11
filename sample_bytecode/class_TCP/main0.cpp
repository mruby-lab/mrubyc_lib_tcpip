#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <WiFi.h>
#include "mrubyc.h"
#include "hal.h"
#include "c_tcp.h"

WiFiServer server(12345);
extern const uint8_t mrbbuf[];

#define MRBC_MEMORY_SIZE (1024*40)
static uint8_t memory_pool[MRBC_MEMORY_SIZE];
int mrubyc(void)
{
  mrbc_init(memory_pool, MRBC_MEMORY_SIZE);
  mrbc_init_class_tcp();
  if( mrbc_create_task(mrbbuf, 0) != NULL ){
    mrbc_run();
  }
  return 0;
}
const char* ssid     = "HR01a-46908F";
const char* password = "819b9a62aa";

// const char* ssid     = "n302mesh";
// const char* password = "n302pw8879";

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("\nESP32 TCP Client (STA mode)");
  WiFi.mode(WIFI_STA);  // ← STAモードで接続
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");

  Serial.println("\n--- Wi-Fi Connection Info ---");

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());

  } else {
    Serial.println("Wi-Fi not connected!");
  }
 
  Serial.println("setup done");
  delay(1000);
  mrubyc();
}

void loop() {
}
