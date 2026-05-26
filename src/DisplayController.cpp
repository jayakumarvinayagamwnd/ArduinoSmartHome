#include "DisplayController.h"

#include <Wire.h>

namespace {
constexpr char kWelcomeMessage[] = "Welcome!";
}

DisplayController::DisplayController()
    : display_(kScreenWidth, kScreenHeight, &Wire, kOledResetPin) {
}

void DisplayController::begin() {
  Wire.begin();

  isInitialized_ = display_.begin(SSD1306_SWITCHCAPVCC, kOledAddress);

  if (!isInitialized_) {
    return;
  }

  showWelcomeMessage();
}

bool DisplayController::isReady() const {
  return isInitialized_;
}

void DisplayController::showWelcomeMessage() {
  renderText(kWelcomeMessage, 2.5, 12, 24);
}

void DisplayController::showClock(const char* text) {
  renderText(text, 2.5, 8, 24);
}

void DisplayController::renderText(const char* text, uint8_t textSize, int16_t x,
                                   int16_t y) {
  if (!isInitialized_) {
    return;
  }

  display_.clearDisplay();
  display_.setTextSize(textSize);
  display_.setTextColor(SSD1306_WHITE);
  display_.setCursor(x, y);
  display_.println(text);
  display_.display();
}