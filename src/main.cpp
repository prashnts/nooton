#include <Adafruit_ADS1X15.h>  //AC DC converter
#include <Arduino.h>

#include "FastLED.h"
#include "lcd_display.h"
#include "webserver.h"
#include "wifi.h"

#define PIXEL_COUNT 1
#define PIXEL_GPIO 40

CRGB pixels[PIXEL_COUNT];

Adafruit_ADS1115 ads;

int16_t adc0;
float volts0;

String ws_data = "";

void setup() {
  Serial.begin(9600);
  Serial.println("boot: init");

  init_wifi();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());

  // FastLED.addLeds<NEOPIXEL, PIXEL_GPIO>(pixels, PIXEL_COUNT);

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1)
      ;
  }

  init_display();
  delay(1000);
  init_server();
}

void loop() {
  // pixels[0] = CRGB::Red;
  // FastLED.show();

  adc0 = ads.readADC_SingleEnded(0);
  volts0 = ads.computeVolts(adc0);

  // // Push out the read values
  // Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  ");
  // Serial.print(volts0); Serial.println("V");

  // volts0 = random(100) * 3.3/100;
  display_data(WiFi.localIP(), volts0);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Hostname: ");
  Serial.println(WiFi.getHostname());

  ws_data = String(volts0, 4);
  ws.printfAll(ws_data.c_str());
  delay(30);
}
