#ifndef SLMUSIC_MUSIC_H
#define SLMUSIC_MUSIC_H

#include <math.h>
#include "Common.h"
#include "Utilities.h"

namespace slm
{
  // Environment variables
  namespace _ENV
  {
    // Middle A pitch
    extern Hertz A4;
    // Time signature
    extern int BAR;
    extern int BEAT;
    // Beats per minute
    extern int BPM;
  }

  // Sets pitch of middle A
  void setMiddleAPitch(Hertz pitch);

  // Sets time signature in the format "bar/beat" (e.g. "3/8")
  void setTimeSignature(const char* signature);

  // Sets beats per minute
  void setBPM(int bpm);

  enum Scale { C, D, E, F, G, A, B };
  extern int notes[7];

  class Note
  {
  private:
    int m_pitch;
    float m_length;
    bool m_isRest;

  public:
    Note();
    Note(const Note& note);
    // Sets the pitch and length of the note in the format: Note("C#3", "1/4");
    // Use "R" as pitch for rest
    Note(const char* pitch, const char* length);

    Note& operator=(const Note& note);

    void SetPitch(const char* pitch);
    void SetLength(const char* length);

    bool IsRest() const { return m_isRest; }

    // Returns the frequency of note
    Hertz GetFrequency() const;
    // Returns note duration in milliseconds
    Millisecond GetDuration() const;
  };

  // future
  /*class Arpeggiator
  {
  private:
    float m_rate;
    Note* m_notes;
    bool m_direction;

  public:
    Arpeggiator(const char* rate);

    void SetRate(const char* rate);
    
    void AddNote(const Note& note);
    void AddNotes(const Note& note);

    void SetDirection(bool direction);
  };*/
}

#endif // SLMUSIC_MUSIC_H