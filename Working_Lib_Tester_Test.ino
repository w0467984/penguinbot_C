#include <PenguinBot.h>

PenguinBot myBot;

void setup() {
  Serial.begin(9600);
}

void loop() {
  myBot.walk(4, 1800, false);
}
