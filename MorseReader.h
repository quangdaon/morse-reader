#include "IntensitySensor.h"

#ifndef HEADER_MORSE_READER
#define HEADER_MORSE_READER
class MorseReader
{
private:
  IntensitySensor &sensor;
  int commandThreshold;
  int charThreshold;
  int wordThreshold;
  int resetThreshold;
  unsigned long timestamp;
  unsigned long lastChange;
  bool charSent;
  int currentSequence[5];
  int currentIndex;
  char currentCharacter;

public:
  MorseReader(IntensitySensor& sensor, int commandThreshold, int charThreshold, int wordThreshold, int resetThreshold);
  void update();
  void reset();
  long getDiff();
  void checkState();
  bool shouldPrint();
  bool checkNewCharacter();
  bool checkNewWord();
  bool checkReset();
  char getCharacter();
};
#endif