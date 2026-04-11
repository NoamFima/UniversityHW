#include "tests.h"

#include <stdio.h>
#include <string.h>
#include <_stdlib.h>

#define K_1 3

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  cipher (in, K_1);
  return strcmp(in, out) != 0;
}

// See full documentation in header file
#include <string.h>

// See full documentation in header file
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "xy z!";
  char out[] = "za b!";
  cipher (in, 2);
  return strcmp(in, out) != 0;
}


// See full documentation in header file
 int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "def";
  char out[] = "cde";
  cipher (in, -1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
  char in[] = "zab";
  char out[] = "xyz";
  cipher (in, -2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
  char in[] = "XYZ";
  char out[] = "ZAB";
  cipher (in, 2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decipher (in, K_1);
  return strcmp(in, out) != 0;

}

// See full documentation in header file
int test_decipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "za b!";
  char out[] = "xy z!";
  decipher (in, 2);
  return strcmp(in, out) != 0;

}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "AB C,!";
  char out[] = "BC D,!";
  decipher (in, -1);
  return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_negative_k ()
{
  char in[] = "XY Z,!";
  char out[] = "AB C,!";
  decipher (in, -3);
  return strcmp(in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_upper_case_positive_k ()
{
  char in[] = "ABC,!";
  char out[] = "XYZ,!";
  decipher (in, 29);
  return strcmp(in, out) != 0;
}
