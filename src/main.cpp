#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include <WiFi.h>
#include "mrubyc.h"
#include "hal.h"
#include "c_tcp.h"
WiFiServer server(12345);

extern const uint8_t mrbbuf[];

// C関数登録の初期化（c_func.cで定義）
//extern "C" void mrbc_init_class_cfunc(struct VM *vm);

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

const char* ssid     = "n302mesh";
const char* password = "n302pw8879";

IPAddress local_IP(172, 29, 247, 212);     // ESP32のIP
IPAddress gateway(172, 29, 240, 1);      // ゲートウェイ（AP自身に設定）
IPAddress subnet(255, 255, 240, 0);      // サブネットマスク
IPAddress primaryDNS(172, 29, 240, 1);     // プライマリDNS

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  // 静的IPアドレスを設定
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS)) {
    Serial.println("Static IP configuration failed!");
  }
  
  // Wi-Fi接続開始
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connected!");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());          // 接続しているWi-Fi名
  Serial.print("IPアドレス: ");
  Serial.println(WiFi.localIP());       // ESP32のIPアドレス
  server.begin();

  Serial.println("setup done");

  delay(10000);

  mrubyc();

}


void loop() {

}