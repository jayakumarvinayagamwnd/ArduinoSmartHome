#pragma once

#include <Arduino.h>

class DisplayController;

class TimerController {
public:
  explicit TimerController(DisplayController& displayController);

  void begin();
  void update();

private:
  void renderCurrentTime();
  void formatClock(char* buffer, size_t bufferSize, unsigned long totalSeconds) const;

  static constexpr unsigned long kIntervalMs = 1000;
  static constexpr size_t kClockBufferSize = 16;

  DisplayController& displayController_;
  unsigned long nextTickAtMs_ = 0;
  unsigned long elapsedSeconds_ = 0;
  bool isRunning_ = false;
};