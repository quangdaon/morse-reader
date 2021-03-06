#include <LiquidCrystal.h>
#include <Arduino.h>
#include "IntensitySensor.h"
#include "MorseCode.h"

const int BRIGHTNESS_STATE_THRESHOLD = 75;
const int MORSE_COMMAND_THRESHOLD = 300;
const int NEW_CHARACTER_THRESHOLD = 500;
const int SPACE_THRESHOLD = 2000;
const int RESET_BASE_THRESHOLD = 10000;
const int PHOTORESISTOR = A0;

LiquidCrystal lcd(2, 3, 8, 9, 10, 11);
IntensitySensor sensor(PHOTORESISTOR, BRIGHTNESS_STATE_THRESHOLD);

unsigned long lastChange = 0;

bool charSent = false;
int currentSequence[5];
int currentIndex = 0;

void reset()
{
  lcd.clear();

  sensor.update();
  sensor.setBase();
  lastChange = millis();
}

void setup()
{
  Serial.begin(115200);

  lcd.begin(16, 2);

  reset();
  Serial.println("Serial On");

  lcd.print("WELCOME!");
  delay(2000);
  lcd.clear();
}

void loop()
{
  sensor.update();

  unsigned long t = millis();
  long diff = t - lastChange;

  if (sensor.hasTurnedOn())
  {
    lastChange = t;
  }

  if (sensor.hasTurnedOff())
  {
    lastChange = t;

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

  if (!sensor.isActive())
  {
    if (diff == NEW_CHARACTER_THRESHOLD)
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

    if (diff >= SPACE_THRESHOLD)
    {
      if (charSent)
      {
        charSent = false;
        lcd.print(" ");
      }
    }

    if (diff >= RESET_BASE_THRESHOLD)
    {
      reset();
    }
  }

  if (t % 400 == 0)
  {
    lcd.blink();
  }
}