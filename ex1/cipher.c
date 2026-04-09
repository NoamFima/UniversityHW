#include "cipher.h"

#include <math.h>
#include <stdio.h>

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

// See full documentation in header file
void cipher(char s[], int k)
{
  for (int char_index = 0; s[char_index] != '\0'; char_index++)
  {
    int round_back;

    // lowercase
    if (s[char_index] >= 'a' && s[char_index] <= 'z')
    {
      round_back = s[char_index] + k;

      if (round_back >= 'a' && round_back <= 'z') {
        s[char_index] = round_back;
      }
      else if (round_back > 'z') {
        s[char_index] = 'a' + (round_back - 'z' - 1);
      }
      else if (round_back < 'a') {
        s[char_index] = 'z' - ('a' - round_back - 1);
      }
    }

    // uppercase
    else if (s[char_index] >= 'A' && s[char_index] <= 'Z')
    {
      round_back = s[char_index] + k;

      if (round_back >= 'A' && round_back <= 'Z') {
        s[char_index] = round_back;
      }
      else if (round_back > 'Z') {
        s[char_index] = 'A' + (round_back - 'Z' - 1);
      }
      else if (round_back < 'A') {
        s[char_index] = 'Z' - ('A' - round_back - 1);
      }
    }
  }
}


// See full documentation in header file
void decipher (char s[], int k)
{
  cipher(s, -k);
}
