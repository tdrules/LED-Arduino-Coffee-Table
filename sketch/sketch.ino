#include <FastLED.h>
#include <SoftwareSerial.h>

#define LED_PIN 2   //pin for LED strip
#define IR_PIN 3    //pin for IR Sensor
#define rxPin 9     //recieving pin Bluetooth
#define txPin 8     //transmission pin Bluetooth
#define NUM_LEDS 20 //# of LED on strip
#define COLOR_ORDER GRB //order of colors

CRGB leds[NUM_LEDS];
SoftwareSerial BTSerial(rxPin,txPin);

void setup() {
  pinMode(IR_PIN, INPUT);
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  BTSerial.begin(9600);
  Serial.begin(9600);

  FastLED.addLeds<WS2812,LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,500);
  FastLED.clear();
  FastLED.show();
}

String messageBuffer = "";
String message = "";

void loop() {

  while (BTSerial.available() > 0) {
    char data = (char) BTSerial.read();
    messageBuffer += data;
    if (data == ";") {
      message = messageBuffer;
      messageBuffer = "";
      
      Serial.print(message); // send to serial monitor
      message = "You sent " + message;
      BTSerial.print(message);  // send back to bluetooth terminal
      
    }
  }
/*
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
*/
}
