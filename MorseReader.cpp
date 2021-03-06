#include <Arduino.h>
#include "MorseCode.h"
#include "MorseReader.h"

MorseReader::MorseReader(IntensitySensor& sensor, int commandThreshold, int charThreshold, int wordThreshold, int resetThreshold)
    : sensor(sensor), commandThreshold(commandThreshold), charThreshold(charThreshold), wordThreshold(wordThreshold), resetThreshold(resetThreshold)
{
  timestamp = millis();
  lastChange = timestamp;
  charSent = false;
  currentIndex = 0;
};

void MorseReader::update()
{
  timestamp = millis();
  checkState();
}

void MorseReader::reset()
{
  lastChange = timestamp;
}

long MorseReader::getDiff()
{
  return timestamp - lastChange;
}

void MorseReader::checkState()
{
  if (sensor.hasTurnedOn())
  {
    Serial.println("Turned On");
    reset();
  }

  if (sensor.hasTurnedOff())
  {
    Serial.println("Turned Off");

    if (getDiff() < commandThreshold)
    {
      Serial.println("Dot");
      currentSequence[currentIndex] = DOT;
    }
    else
    {
      Serial.println("Dash");
      currentSequence[currentIndex] = DASH;
    }

    currentIndex++;
    reset();
  }
}

bool MorseReader::shouldPrint()
{
  return checkNewCharacter() || checkNewWord();
}

bool MorseReader::checkNewCharacter()
{
  if (!sensor.isActive() && getDiff() == charThreshold)
  {
    if (currentIndex > 0)
    {
      currentCharacter = ReadMorseSequence(currentSequence);
      for (int x = 0; x < 5; x++)
      {
        currentSequence[x] = 0;
      }
      currentIndex = 0;
      charSent = true;
      reset();
      return true;
    }
  }

  return false;
}

bool MorseReader::checkNewWord()
{
  if (!sensor.isActive() && getDiff() == wordThreshold)
  {
    if (charSent)
    {
      charSent = false;
      currentCharacter = ' ';
      return true;
    }
  }

  return false;
}

bool MorseReader::checkReset()
{
  return !sensor.isActive() && getDiff() == resetThreshold;
}

char MorseReader::getCharacter()
{
  return currentCharacter;
}
