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

void setup() {

  Serial.begin(115200);
  
  WiFi.softAP("ESP32_Server_AP", "12345678");

  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  // server.begin();

  // ここで mruby/c のタスクを起動
  // xTaskCreate(ruby_task, "ruby_task", 8192, NULL, 5, NULL);
  Serial.println("setup done");

    mrubyc();

}


void loop() {

}