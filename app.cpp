#include <LiquidCrystal.h>
#include <Arduino.h>
#include "IntensitySensor.h"
#include "MorseReader.h"
#include "MorseCode.h"

const int BRIGHTNESS_STATE_THRESHOLD = 75;
const int MORSE_COMMAND_THRESHOLD = 300;
const int NEW_CHARACTER_THRESHOLD = 500;
const int SPACE_THRESHOLD = 2000;
const int RESET_BASE_THRESHOLD = 10000;
const int PHOTORESISTOR = A0;

LiquidCrystal lcd(2, 3, 8, 9, 10, 11);
IntensitySensor sensor(PHOTORESISTOR, BRIGHTNESS_STATE_THRESHOLD);
MorseReader morseReader(sensor, MORSE_COMMAND_THRESHOLD, NEW_CHARACTER_THRESHOLD, SPACE_THRESHOLD, RESET_BASE_THRESHOLD);

unsigned long lastChange = 0;

bool charSent = false;
int currentSequence[5];
int currentIndex = 0;

void reset()
{
  lcd.clear();

  sensor.update();
  sensor.setBase();
  morseReader.reset();
  lastChange = millis();
}

void setup()
{
  Serial.begin(115200);
  lcd.begin(16, 2);

  Serial.println("Serial On");

  lcd.print("WELCOME!");
  delay(2000);

  reset();
}

void loop()
{
  sensor.update();
  morseReader.update();

  if (morseReader.shouldPrint())
    lcd.print(morseReader.getCharacter());

  if (morseReader.checkReset())
    reset();

  if (millis() % 400 == 0)
    lcd.blink();
}