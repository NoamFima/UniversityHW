#include "tests.h"

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
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
  // your code goes here
}

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
  // your code goes here
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
  // your code goes here
}

// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
  // your code goes here
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decipher (in, K_1);
  return strcmp (in, out) != 0;
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
