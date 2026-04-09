#include "tests.h"

#include <string.h>
#include <_stdlib.h>

#define K_1 3

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  cipher (in, K_1);
  return strcmp (in, out) != 0;

}

// See full documentation in header file
#include <string.h>

// See full documentation in header file
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "xy z!";
  char out[] = "za b!";
  cipher (in, 2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "def";
  char out[] = "abc";
  cipher (in, -1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
  char in[] = "zab";
  char out[] = "xyz";
  cipher (in, 2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
  char in[] = "ABC";
  char out[] = "DDD";
  cipher (in, 2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_positive_k ()
{

}

// See full documentation in header file
int test_decipher_cyclic_lower_case_special_char_positive_k ()
{
  // your code goes here
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_special_char_negative_k ()
{
  // your code goes here
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_negative_k ()
{
  // your code goes here
}

// See full documentation in header file
int test_decipher_cyclic_upper_case_positive_k ()
{
  // your code goes here
}
