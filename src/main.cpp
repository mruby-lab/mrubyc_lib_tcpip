#include <Arduino.h>

#include <stdio.h>
#include <stdlib.h>
#include "mrubyc.h"

extern const uint8_t mrbbuf[];

#define MRBC_MEMORY_SIZE (1024*20)
static uint8_t memory_pool[MRBC_MEMORY_SIZE];


void setup() {
  Serial.begin(115200);
  Serial.println("setup done");
}

int mrubyc(void)
{
  mrbc_init(memory_pool, MRBC_MEMORY_SIZE);

  if( mrbc_create_task(mrbbuf, 0) != NULL ){
    mrbc_run();
  }

  return 0;
}

void loop() {
  mrubyc();
}


