#include "FastLED.h"

#define LED_PIN 2   //pin for LED strip
#define IR_PIN 3    //pin for IR Sensor
#define NUM_LEDS 20 //# of LED on strip
#define COLOR_ORDER GRB //order of colors

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(IR_PIN, INPUT);
  FastLED.addLeds<WS2812,LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  //TODO Bluetooth sensor
  for (int i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(255 - i*10, 0, i*10);
    if (digitalRead(IR_PIN) == LOW) {
      leds[i] = CRGB(255,0,0);
    }
    FastLED.show();
    delay(50);
  }
  for (int i=NUM_LEDS;i>0;i--) {
    leds[i] = CRGB(55 + i*10, 0, 20 - i*10 );
    if (digitalRead(IR_PIN) == LOW) {
      leds[i] = CRGB(255,0,0);
    }
    FastLED.show();
    delay(50);
  }
  
}
