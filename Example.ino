#include "SLMusic.h"
using namespace slm;

#define REST(x) (Note("R", x))

Led testLed(9);          // led at pin 9
Buzzer testBuzzer(5);    // buzzer at pin 5

int testNotesLength = 40;
int loopCount = 2;

Note testNotes[] = {
  Note("C3", "4/6"), Note("D#3", "5/6"), Note("F3", "3/6"),
  Note("C3", "4/6"), Note("D#3", "5/6"), Note("F3", "3/6"),
  Note("C3", "4/6"), Note("D#3", "5/6"), Note("F3", "3/6"),
  Note("C3", "4/6"), Note("D#3", "5/6"), REST("3/6"),

  Note("C4", "1/3"),  Note("F4", "1/6"), Note("C5", "1/12"), Note("F4", "1/12"),
  Note("D#4", "5/6"), Note("F4", "1/3"), Note("D#4", "1/6"),

  Note("C4", "1/3"),  Note("F4", "1/6"), Note("C5", "1/12"), Note("F4", "1/12"),
  Note("D#4", "5/6"), Note("F4", "3/6"),

  Note("C4", "1/3"),  Note("F4", "1/6"), Note("C5", "1/12"), Note("F4", "1/12"),
  Note("D#4", "5/6"), Note("F4", "1/3"), Note("D#4", "1/6"),

  Note("C4", "1/3"),  Note("F4", "1/6"), Note("C5", "1/12"), Note("F4", "1/12"),
  Note("D#4", "5/6"), Note("F4", "1/6"), Note("A#4", "1/6"), Note("F5", "1/6")
};

void setup()
{
  // environment variables...
  setMiddleAPitch(440);
  setTimeSignature("3/4");
  setBPM(168);
}

void loop()
{
  Millisecond delta = millis();

  if (!testBuzzer.NotesLeft() && loopCount)
  {
    testBuzzer.PushNotes(testNotes, testNotesLength);
    loopCount--;
  }

  // When a new note starts playing, light the led and fade it down
  if (testBuzzer.VUpdate(delta))
  {
    // Here the fade is synchronized with the note
    testLed.Fade(255, 0, testBuzzer.GetCurrentNote().GetDuration());
  }

  testLed.VUpdate(delta);
}