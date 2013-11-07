#include "Music.h"

namespace slm
{
  // octave 4, A = 0
  int notes[] = {-9, -7, -5, -4, -2, 0, 2};

  namespace _ENV
  {
    Hertz A4 = 440;
    int BAR = 4;
    int BEAT = 4;
    int BPM = 120;
  }

  void setMiddleAPitch(Hertz pitch)
  {
    _ENV::A4 = pitch;
  }

  void setTimeSignature(const char* signature)
  {
    int index = strcspn(signature, "/");
    _ENV::BAR = stringToInt(signature);
    _ENV::BEAT = stringToInt(signature, index + 1);
  }

  void setBPM(int bpm)
  {
    _ENV::BPM = bpm;
  }

  Note::Note()
  {
    m_isRest = true;
  }

  Note::Note(const Note& note)
  {
    m_pitch = note.m_pitch;
    m_length = note.m_length;
    m_isRest = note.m_isRest;
  }

  Note::Note(const char* pitch, const char* length)
  {
    SetPitch(pitch);
    SetLength(length);
  }

  Note& Note::operator=(const Note& note)
  {
    m_pitch = note.m_pitch;
    m_length = note.m_length;
    m_isRest = note.m_isRest;
    return *this;
  }

  void Note::SetPitch(const char* pitch)
  {
    m_isRest = false;

    // Finding out the distance of the note from A
    switch (pitch[0])
    {
    case 'C':
      m_pitch = notes[C];
      break;
    case 'D':
      m_pitch = notes[D];
      break;
    case 'E':
      m_pitch = notes[E];
      break;
    case 'F':
      m_pitch = notes[F];
      break;
    case 'G':
      m_pitch = notes[G];
      break;
    case 'A':
      m_pitch = notes[A];
      break;
    case 'B':
      m_pitch = notes[B];
      break;
    // 'R' for rest
    case 'R':
      m_isRest = true;
      return;
    }

    // Put the note in the right octave
    int octave = pitch[strlen(pitch) - 1] - '0';
    // -4 because middle A is A4
    m_pitch += (octave - 4) * 12;

    // Apply sharps(#) and flats(b)
    for (int i = 1; i < strlen(pitch) - 1; i++)
    {
      switch (pitch[i])
      {
      case '#':
        m_pitch++;
        break;
      case 'b':
        m_pitch--;
        break;
      }
    }
  }

  void Note::SetLength(const char* length)
  {
    int index = strcspn(length, "/");
    // If the note length is an integer
    if (index == strlen(length))
    {
      m_length = stringToInt(length);
    }
    // If the note length is a fraction
    else
    {
      float numerator = stringToInt(length);
      float denominator = stringToInt(length, index + 1);
      m_length = numerator / denominator;
    }
  }

  Hertz Note::GetFrequency() const
  {
    return pow(2, m_pitch / 12.f) * _ENV::A4 + 0.5;
  }

  Millisecond Note::GetDuration() const
  {
    float beatsPerSecond = 60.f / _ENV::BPM;
    float timeSignature = _ENV::BAR / (float)_ENV::BEAT;
    return beatsPerSecond * timeSignature * 4 * m_length * 1000 + 0.5;
  }
}