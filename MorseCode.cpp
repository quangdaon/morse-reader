#include "MorseCode.h"

int *GetMorseSequence(char character)
{
  static int sequence[5];
  for (auto entry : MorseMap)
  {
    if (entry.character == character)
    {
      for (int i = 0; i < 5; ++i)
      {
        sequence[i] = entry.sequence[i];
      }
    }
  }

  return sequence;
}

char ReadMorseSequence(int sequence[5])
{
  for (auto entry : MorseMap)
  {
    bool match = true;
    
    for (int i = 0; i < 5; ++i)
    {
      if(sequence[i] != entry.sequence[i]) {
        match = false;
        break;
      }
    }

    if(match)
      return entry.character;
  }
}