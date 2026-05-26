#pragma once

#include <Adafruit_SSD1306.h>

class DisplayController {
public:
  DisplayController();

  void begin();
  bool isReady() const;
  void showWelcomeMessage();
  void showClock(const char* text);

private:
  void renderText(const char* text, uint8_t textSize, int16_t x, int16_t y);

  static constexpr uint8_t kScreenWidth = 128;
  static constexpr uint8_t kScreenHeight = 64;
  static constexpr int8_t kOledResetPin = -1;
  static constexpr uint8_t kOledAddress = 0x3C;

  Adafruit_SSD1306 display_;
  bool isInitialized_ = false;
};