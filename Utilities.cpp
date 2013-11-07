#include "Utilities.h"

namespace slm
{
  int stringToInt(const char* str, int index)
  {
    char* temp;
    if (index)
    {
      return strtol(&str[index], &temp, 10);
    }
    return strtol(str, &temp, 10);
  }
}