#include "TimerController.h"

#include "DisplayController.h"

#include <stdio.h>

TimerController::TimerController(DisplayController& displayController)
    : displayController_(displayController) {
}

void TimerController::begin() {
  elapsedSeconds_ = 0;
  nextTickAtMs_ = millis() + kIntervalMs;
  isRunning_ = true;

  renderCurrentTime();
}

void TimerController::update() {
  if (!isRunning_) {
    return;
  }

  const unsigned long now = millis();

  if (static_cast<long>(now - nextTickAtMs_) < 0) {
    return;
  }

  // Catch up cleanly if loop work ever delays the exact second boundary.
  do {
    ++elapsedSeconds_;
    nextTickAtMs_ += kIntervalMs;
  } while (static_cast<long>(now - nextTickAtMs_) >= 0);

  renderCurrentTime();
}

void TimerController::renderCurrentTime() {
  char buffer[kClockBufferSize];

  formatClock(buffer, sizeof(buffer), elapsedSeconds_);
  displayController_.showClock(buffer);
}

void TimerController::formatClock(char* buffer, size_t bufferSize,
                                  unsigned long totalSeconds) const {
  const unsigned long hours = totalSeconds / 3600;
  const unsigned long minutes = (totalSeconds % 3600) / 60;
  const unsigned long seconds = totalSeconds % 60;

  snprintf(buffer, bufferSize, "%02lu:%02lu:%02lu", hours, minutes, seconds);
}