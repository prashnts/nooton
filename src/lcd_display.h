#include <Adafruit_SSD1327.h>  // SSD1327 * OLED * 128x128 * Gray

#define TEXT_SIZE 3
#define OLED_RESET -1

Adafruit_SSD1327 display(128, 128, &Wire, OLED_RESET, 1000000);

void init_display() {
  if (!display.begin(0x3C)) {
    Serial.println("Unable to initialize OLED");
    while (1) {
      yield();
    }
  }
  display.clearDisplay();
  display.display();
  display.setTextSize(TEXT_SIZE);
  display.setTextWrap(true);
  display.setTextColor(SSD1327_WHITE);
}

void display_data(IPAddress ip, float force) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("IP Address: \n");
  display.print(ip);

  display.setCursor(30, 75);
  display.setTextSize(TEXT_SIZE);
  display.print(force);
  display.display();
}
