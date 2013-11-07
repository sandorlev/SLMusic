#include "Output.h"

namespace slm
{
  // Set digital state
  void Output::SetState(bool state)
  {
    m_state = state;
    m_value = state * 255;
    digitalWrite(m_pin, state);
  }

  void Output::ToggleState()
  {
    if (m_state)
    {
      SetState(OFF);
    }
    else
    {
      SetState(ON);
    }
  }

  // Set 'analog' state
  void Output::SetValue(int value)
  {
    m_value = value;
    m_state = value;
    analogWrite(m_pin, value);
  }

  void Led::Fade(int startValue, int endValue, Millisecond duration)
  {
    m_fadeStartValue = startValue;
    m_fadeEndValue = endValue;
    m_fadeDuration = duration;
    m_fadeStartTime = 0;
    m_fading = true;
  }

  bool Led::VUpdate(Millisecond delta)
  {
    if (m_fading)
    {
      // If the fade did not start yet
      if (!m_fadeStartTime)
      {
        m_value = m_fadeStartValue;
        m_fadeStartTime = delta;
      }

      Millisecond timeFromStart = delta - m_fadeStartTime;
      Millisecond timeFromLastFade = delta - m_lastFadeUpdate;

      // If the fade is still going on
      if (timeFromStart < m_fadeDuration)
      {
        float difference = m_fadeEndValue - m_fadeStartValue;
        Millisecond fadeInterval = m_fadeDuration / abs(difference) + 0.5;

        if (timeFromLastFade >= fadeInterval)
        {
          m_value += sgn(difference);
          m_lastFadeUpdate = delta;
        }
      }
      // If the fade stopped
      else
      {
        m_value = m_fadeEndValue;
        m_fadeStartTime = 0;
        m_fading = false;
      }
    }

    SetValue(m_value);
    m_lastUpdate = delta;
    return false;
  }

  void Buzzer::PushNote(const Note& note)
  {
    m_noteQueue.PushBack(note);
  }

  void Buzzer::PushNotes(Note* notes, int length)
  {
    for (int i = 0; i < length; i++)
    {
      m_noteQueue.PushBack(notes[i]);
    }
  }

  bool Buzzer::VUpdate(Millisecond delta)
  {
    bool newNoteStarted = false;

    // If there are still notes left
    if (m_noteQueue.Size())
    {
      // If there is no note playing at the moment
      if (!m_currentNoteStart)
      {
        m_currentNoteStart = delta;
        //m_currentNote = m_noteQueue.PopFront();
        m_currentNote = m_noteQueue.Front();
        newNoteStarted = true;
      }

      Millisecond timeFromStart = delta - m_currentNoteStart;

      if (timeFromStart < m_currentNote.GetDuration())
      {
        // If note is not a rest, play it
        if (!m_currentNote.IsRest())
        {
          tone(m_pin, m_currentNote.GetFrequency(), 0);
        }
        // If note is a rest, do not count it as new
        else
        {
          newNoteStarted = false;
        }
      }
      // If done with current note
      else
      {
        noTone(m_pin);
        // shouldn't be here...
        m_noteQueue.PopFront();
        m_currentNoteStart = 0;
      }
    }

    m_lastUpdate = delta;
    return newNoteStarted;
  }
}