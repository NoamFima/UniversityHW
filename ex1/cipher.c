#include "cipher.h"

#include <math.h>
#include <stdio.h>

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

// See full documentation in header file
#define BOTTOM_CAPITAL 'A'
#define BOTTOM_LOWER 'a'
#define TOP_LOWER 'z'
#define TOP_CAPITAL 'Z'
#define ALPHABET_MAX 26
void cipher(char s[], int k)
{
  k = k % ALPHABET_MAX;
  for (int char_index = 0; s[char_index] != '\0'; char_index++)
  {

      if (s[char_index] >= BOTTOM_LOWER && s[char_index] <= TOP_LOWER) {

        s[char_index] = ((s[char_index] - BOTTOM_LOWER + k + ALPHABET_MAX) % ALPHABET_MAX) + BOTTOM_LOWER; // formula converts the letter values like the alphabet from 0-26
                                                                                       // and makes sure negative k's dont screw up the modulo by adding 26 at the end
                                                                                       // for example: a-a = 0 + k (=3) = 3 + 26 =29 % 26 = 3 + 'a' = d

      }else if (s[char_index] >= BOTTOM_CAPITAL && s[char_index] <= TOP_CAPITAL) {
        s[char_index] = ((s[char_index] - BOTTOM_CAPITAL + k + ALPHABET_MAX) % ALPHABET_MAX) + BOTTOM_CAPITAL;
      }

  }
}


// See full documentation in header file
void decipher (char s[], int k)
{
  cipher(s, -k);
}
