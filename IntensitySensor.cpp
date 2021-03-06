#include <Arduino.h>
#include "IntensitySensor.h"

IntensitySensor::IntensitySensor(int s, int th)
{
  pin = s;
  state = false;
  threshold = th;
  base = 0;
}

void IntensitySensor::update() {
  int val = analogRead(pin);
  setIntensity(val);
}

void IntensitySensor::setBase()
{
  base = intensity;
}

void IntensitySensor::setIntensity(int val)
{
  intensity = val;
}

bool IntensitySensor::isActive() {
  return intensity - base > threshold;
}

bool IntensitySensor::hasTurnedOn()
{
  if (!state && isActive())
  {
    state = true;
    return true;
  }

  return false;
}

bool IntensitySensor::hasTurnedOff()
{
  if (state && !isActive())
  {
    state = false;
    return true;
  }

  return false;
}