#include <Arduino.h>
#include "FastLED.h"
#include <Adafruit_ADS1X15.h>

#define PIXEL_COUNT 1
#define PIXEL_GPIO 40

CRGB pixels[PIXEL_COUNT];

Adafruit_ADS1115 ads;

int16_t adc0;
float volts0;

void setup() {
  Serial.begin(115200);
  Serial.println("boot: init");

  FastLED.addLeds<NEOPIXEL, PIXEL_GPIO>(pixels, PIXEL_COUNT);

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

}


void loop() {
    pixels[0] = CRGB::Red;
    FastLED.show();

    adc0 = ads.readADC_SingleEnded(0);
    volts0 = ads.computeVolts(adc0);

    // Push out the read values
    Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");

    delay(30);
}
