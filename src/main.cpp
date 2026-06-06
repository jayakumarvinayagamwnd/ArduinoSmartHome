#include <Arduino.h>

#include "DisplayController.h"
#include "TimerController.h"

namespace {
DisplayController displayController;
TimerController timerController(displayController);
}

void setup() {
  Serial.begin(115200);

  displayController.begin();
  timerController.begin();
}

void loop() {
  timerController.update();
}