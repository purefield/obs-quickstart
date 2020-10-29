/* Start of Code */

#include "FastLED.h"

// How many leds are connected?
#define NUM_LEDS 89
#define BRIGHTNES 35
#define FACTOR 50
int factor;
int brightnes;

// Define the Pins
#define DATA_PIN 8
#define SENSOR_PIN A0
#define BUFFER 20

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  factor = FACTOR;
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  // Change led colors
  for (int led = 0; led < NUM_LEDS; led++) {
    leds[led] = CRGB::Green;
  }
  Serial.begin(9600);
  Serial.println("<LED is ready>");
  updateBrightnes(BRIGHTNES);
}

void loop() {
  readFactor();
  senseBrightness();
}

void senseBrightness() {
  int analogValue = analogRead(SENSOR_PIN);
  int newBrightnes = (analogValue / 8) * factor / 128;

  //Serial.print("Sensor = ");
  //Serial.println(analogValue);
  //Serial.print("New Brightnes = ");
  //Serial.println(newBrightnes);
  if (((100 * newBrightnes) > (brightnes * (100 + BUFFER)) ||
       (100 * newBrightnes) < (brightnes * (100 - BUFFER))) &&
      newBrightnes >= 0 &&
      newBrightnes <= 100) {
    updateBrightnes(newBrightnes / 5 * 5);
    //Serial.print(100 * newBrightnes);
    //Serial.print(" > ");
    //Serial.print(String(brightnes * (100 + BUFFER)));
    //Serial.print(":");
    //Serial.println(String((100 * newBrightnes) > (brightnes * (100 + BUFFER))));
    //Serial.print(100 * newBrightnes);
    //Serial.print(" < ");
    //Serial.print(String(brightnes * (100 - BUFFER)));
    //Serial.print(":");
    //Serial.println(String((100 * newBrightnes) < (brightnes * (100 - BUFFER))));
  }
}

void readFactor() {
  if (Serial.available() > 0) {
    int input = Serial.parseInt();
    if (input != factor && 
        input >= 0 && 
        input <= 100) {
      factor = input;
      Serial.print("Factor = ");
      Serial.println(String(factor));
      senseBrightness();
    }
  }
}

void updateBrightnes( int newBrightnes) {
  brightnes = newBrightnes;
  Serial.print("Brightnes = ");
  Serial.println(String(brightnes));
  FastLED.setBrightness(brightnes);
  FastLED.show();
}
/* End of Code */
