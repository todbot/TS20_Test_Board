// TS20_test1.ino -- Test TS20 Capacitive Touch Sensor chip
// 10 Mar 2024 - @todbot / Tod Kurt
// Part of https://github.com/todbot/TS20_Test_Board/
//
// This code based off of "ADS_Touch_Sensor_TS20.ino" and
// "Arduino_TS20.ino" from: https://github.com/yni2yni/TS20
//
// Test setup:
// - TS20 Touch Test Board,
//   - with zero-ohm resistors and no caps on pad lines (low impedance)
// - wired to Raspberry Pi Pico pins GP4 & GP5 (I2C0)
// - Neopixel strip wired to Pico pin GP22
// Sketch is compiled using arduino-pico core

#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#include "TS20.h"

// Pico pins used
const int SDA_PIN = 4;  // default Wire SDA on arduino-pico
const int SCL_PIN = 5;  // default Wire SCL on arduino-pico
const int LED_PIN = 22;
// LED constants
const int NUM_LEDS = 64;
const int LED_BRIGHTNESS = 10;

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// used to map serpentine 8x8 LED grid to how buttons are laid out
// index is pad number (0-based), output is LED number
const int pad_to_led[] = {
  0, 15, 16, 31, 32,
  1, 14, 17, 30, 33,
  2, 13, 18, 29, 34,
  3, 12, 19, 28, 35,
  4, 11, 20, 27, 26,
  63, // last LED is for "is noisy" bit
};

TS20 ts20 = TS20();


void setup() {
  //Wire.setClock(100000);  // run I2C at 100 kHz
  Wire.setClock(400000);  // run I2C at 400 kHz
  Serial.begin(115200);

  leds.begin();
  leds.setBrightness(LED_BRIGHTNESS);

  delay(100);    // wait for 100 msec, as per datasheet
  ts20.begin();  // Initialize TS20
  delay(100);    // wait for 100 msec as per datasheet
}

const int dim_by = 1;
void loop() {
  leds.clear();

  // for( int i=0; i<NUM_LEDS; i++) {
  //   uint32_t c = leds.getPixelColor(i);
  //   uint8_t r = (c & 0xff0000) >> 16;
  //   uint8_t g = (c & 0x00ff00) >> 8;
  //   uint8_t b = (c & 0x0000ff) >> 0;
  //   leds.setPixelColor(i, (c > dim_by) ? c-dim_by : 0);
  // }

  uint32_t touches = ts20.getTouches();
  Serial.printf("touches: %08lx  ", touches);
  for (int i = 0; i < 21; i++) {        // 20 pads + "is noisy" bit
    bool touch = (touches & (1 << i));  // touch for specific pad
    Serial.print(touch ? "1" : "0");
    // leds.setPixelColor(i, touch ? 0xff00ff : 0x000000);
    leds.setPixelColor(pad_to_led[i], touch ? 0xff00ff : 0x000000);
  }
  Serial.println();

  leds.show();

  //ts20.readSensitivity();
  //ts20.readRdCh();

  delay(50);
}
