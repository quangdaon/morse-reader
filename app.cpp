#include <LiquidCrystal.h>
#include <Arduino.h>
#include "MorseCode.h"

#pragma region Config
const int BRIGHTNESS_STATE_THRESHOLD = 75;
const int MORSE_COMMAND_THRESHOLD = 300;
const int NEW_CHARACTER_THRESHOLD = 500;
const int SPACE_THRESHOLD = 2000;
const int RESET_BASE_THRESHOLD = 10000;
#pragma endregion

LiquidCrystal lcd(2, 3, 8, 9, 10, 11);
const int PHOTORESISTOR = A0;

unsigned long lastChange = 0;

int baseBrightness = 0;
bool state = false;
bool charSent = false;
int currentSequence[5];
int currentIndex = 0;

void reset()
{
  lcd.clear();

  int val = analogRead(A0);
  baseBrightness = val;
  state = false;
  lastChange = millis();
}

void setup()
{
  Serial.begin(115200);

  lcd.begin(16, 2);

  reset();
  Serial.println("Serial On");
}

void loop()
{
  int val = analogRead(A0);
  unsigned long t = millis();
  int isOn = val - baseBrightness > BRIGHTNESS_STATE_THRESHOLD;
  long diff = t - lastChange;

  if (!state && isOn)
  {
    state = true;
    lastChange = t;

    char ts = t;
  }

  if (state && !isOn)
  {
    state = false;
    lastChange = t;

    char ts = t;

    if (diff < MORSE_COMMAND_THRESHOLD)
    {
      currentSequence[currentIndex] = DOT;
    }
    else
    {
      currentSequence[currentIndex] = DASH;
    }

    currentIndex++;
  }

  if (!state && diff == NEW_CHARACTER_THRESHOLD)
  {
    if (currentIndex > 0)
    {
      lastChange = t;
      char character = ReadMorseSequence(currentSequence);
      lcd.print(character);
      for (int x = 0; x < 5; x++)
      {
        currentSequence[x] = 0;
      }
      currentIndex = 0;
      charSent = true;
    }
  }

  if (!state && diff >= SPACE_THRESHOLD)
  {
    if (charSent)
    {
      charSent = false;
      lcd.print(" ");
    }
  }

  if (!state && diff >= RESET_BASE_THRESHOLD)
  {
    reset();
  }

  if (t % 400 == 0)
  {
    lcd.blink();
  }
}