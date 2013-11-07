#ifndef SLMUSIC_COMMON_H
#define SLMUSIC_COMMON_H

#include <stdlib.h>
#include <stdint.h>

#define ON  true
#define OFF false

#define abs(n) ((n) < 0 ? (-(n)) : (n))
#define sgn(n) ((n) < 0 ? -1 : 1)

// Needed for Visual Micro
#ifndef OUTPUT
#define OUTPUT 0x1
#endif // OUTPUT

void tone(uint8_t, unsigned int, unsigned long);
void noTone(uint8_t);

extern "C"
{
  unsigned long millis();
  void delay(unsigned long);
  void pinMode(uint8_t, uint8_t);
  void analogWrite(uint8_t, int);
  void digitalWrite(uint8_t, uint8_t);
}

namespace slm
{
  typedef unsigned long Millisecond;
  typedef unsigned int Hertz;
}

#endif // SLMUSIC_COMMON_H