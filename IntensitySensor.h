#ifndef HEADER_INTENSITY_SENSOR
#define HEADER_INTENSITY_SENSOR
class IntensitySensor
{
protected:
  bool state;
  int pin;
  int base;
  int threshold;
  int intensity;

public:
  IntensitySensor(int s, int th);
  void update();
  void setBase();
  void setIntensity(int val);
  bool isActive();
  bool hasTurnedOn();
  bool hasTurnedOff();
};
#endif