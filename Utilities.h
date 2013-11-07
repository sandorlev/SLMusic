#ifndef SLMUSIC_UTILITIES_H
#define SLMUSIC_UTILITIES_H

#include <stdlib.h>
#include <string.h>

#define SLM_MAXQUEUESIZE 128

namespace slm
{
  int stringToInt(const char* str, int index = 0);

  template <class T>
  class Queue
  {
  private:
    T* m_data;
    int m_maxSize;
    int m_elements;
    //int m_beginning;
    int m_end;

  public:
    Queue(int maxSize = SLM_MAXQUEUESIZE);
    Queue(const Queue& queue);
    ~Queue();

    //const T& Front() const { return m_data[m_beginning]; }
    const T& Front() const { return m_data[0]; }
    const T& Back() const { return m_data[m_end]; }

    int Size() const { return m_elements; }

    void PushBack(const T& element);
    //T PopFront();
    void PopFront();
  };

  // Queue implementation
  template <class T>
  Queue<T>::Queue(int maxSize)
  {
    m_data = new T[maxSize + 1];
    m_maxSize = maxSize;
    m_elements = 0;
    //m_beginning = 0;
    m_end = 0;
  }

  template <class T>
  Queue<T>::Queue(const Queue& queue)
  {
    m_maxSize = queue.m_maxSize;
    m_elements = queue.m_elements;
    //m_beginning = queue.m_beginning;
    m_end = queue.m_end;
    m_data = new T[m_maxSize + 1];

    for (int i = 0; i < queue.Size(); i++)
    {
      m_data[i] = queue.m_data[i];
    }
  }

  template <class T>
  Queue<T>::~Queue()
  {
    delete[] m_data;
  }

  template <class T>
  void Queue<T>::PushBack(const T& element)
  {
    if (m_elements > m_maxSize)
    {
      return;
    }

    m_data[m_end++] = element;
    m_elements++;

    if (m_end > m_maxSize)
    {
      m_end -= m_maxSize + 1;
    }
  }

  // Doesn't work, no idea why
  // hard to debug without error messages
  /*template <class T>
  T Queue<T>::PopFront()
  {
    if (m_elements < 1)
    {
      return;
    }

    T element = T(m_data[m_beginning++]);
    m_elements--;

    if (m_beginning > m_maxSize)
    {
      m_beginning -= m_maxSize + 1;
    }

    return element;
  }*/

  template <class T>
  void Queue<T>::PopFront()
  {
    if (m_elements < 1)
    {
      return;
    }

    m_elements--;
    m_end--;

    for (int i = 0; i < m_elements; i++)
    {
      m_data[i] = m_data[i + 1];
    }
  }
}

#endif // SLMUSIC_UTILITIES_H