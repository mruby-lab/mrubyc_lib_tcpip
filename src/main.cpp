#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include "mrubyc.h"
#include "hal.h"
#include "c_tcp.h"

extern const uint8_t mrbbuf[];

// C関数登録の初期化（c_func.cで定義）
//extern "C" void mrbc_init_class_cfunc(struct VM *vm);

#define MRBC_MEMORY_SIZE (1024*40)
static uint8_t memory_pool[MRBC_MEMORY_SIZE];

int mrubyc(void)
{
  mrbc_init(memory_pool, MRBC_MEMORY_SIZE);

  // // ★ ここで C関数を登録
  // mrbc_init_class_cfunc(0);
  void mrbc_init_class_tcp(void);

  if( mrbc_create_task(mrbbuf, 0) != NULL ){
    mrbc_run();
  }

  return 0;
}

void setup() {
  Serial.begin(115200);
  Serial.println("setup done");
  mrubyc();
}


void loop() {
  
}

