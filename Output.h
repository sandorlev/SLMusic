#ifndef SLMUSIC_OUTPUT_H
#define SLMUSIC_OUTPUT_H

#include "Common.h"
#include "Music.h"
#include "Utilities.h"

namespace slm
{
  class Output
  {
  protected:
    uint8_t m_pin;
    bool m_state;
    int m_value;
    Millisecond m_lastUpdate;

  public:
    Output(uint8_t pin) : \
      m_pin(pin), m_lastUpdate(0) { pinMode(pin, OUTPUT); SetState(OFF); }

    // Initialize with given state
    Output(uint8_t pin, bool state) : \
      m_pin(pin), m_lastUpdate(0) { pinMode(pin, OUTPUT); SetState(state); }

    uint8_t GetPin() const { return m_pin; }

    // Digital methods
    void SetState(bool state);
    void ToggleState();
    bool GetState() const { return m_state; }

    // PWM methods
    void SetValue(int value);
    int GetValue() const { return m_value; }

    virtual bool VUpdate(Millisecond delta) = 0;
  };

  class Led : public Output
  {
  private:
    bool m_fading;
    int m_fadeStartValue;
    int m_fadeEndValue;
    Millisecond m_lastFadeUpdate;
    Millisecond m_fadeStartTime;
    Millisecond m_fadeDuration;

  public:
    Led(uint8_t pin) : \
      Output(pin), m_fading(false) { }

    Led(uint8_t pin, bool state) : \
      Output(pin, state), m_fading(false) { }

    // Fades the led 'internally', but does not update its value
    void Fade(int startValue, int endValue, Millisecond time);
    bool IsFading() const { return m_fading; }

    // Updates the led, keeping track of current fade status
    bool VUpdate(Millisecond delta);
  };

  class Buzzer : public Output
  {
  private:
    Millisecond m_currentNoteStart;
    Note m_currentNote;
    Queue<Note> m_noteQueue;

  public:
    Buzzer(uint8_t pin) : \
      Output(pin), m_currentNoteStart(0) { }

    Buzzer(uint8_t pin, bool state) : \
      Output(pin, state), m_currentNoteStart(0) { }

    const Note& GetCurrentNote() const { return m_currentNote; }
    bool NotesLeft() const { return m_noteQueue.Size(); }

    void PushNote(const Note& note);
    void PushNotes(Note* notes, int length);

    // Consumes note queue, returns true if new note started playing
    bool VUpdate(Millisecond delta);
  };
}

#endif // SLMUSIC_OUTPUT_H