#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("setup done");
}

void loop() {
  // put your main code here, to run repeatedly:

  while(1) {
    Serial.println("mruby/c !");
    delay(1000);
  }
}
