#ifndef HEADER_INTENSITY_SENSOR
#define HEADER_INTENSITY_SENSOR
class IntensitySensor
{
private:
  bool state;
  int pin;
  int base;
  int threshold;
  int intensity;

public:
  IntensitySensor(int pin, int threshold);
  void update();
  void setBase();
  void setIntensity(int val);
  bool isActive();
  bool hasTurnedOn();
  bool hasTurnedOff();
};
#endif