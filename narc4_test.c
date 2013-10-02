#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "narc4.h"

void
test(const char * plaintext, const char * key, const char * expect)
{
  unsigned int keysize = strlen(key), keystreamsize, plaintextsize = keystreamsize = strlen(plaintext);
  unsigned char S[256], * K = malloc(keystreamsize);
  char * text = malloc(plaintextsize);
  if (K == NULL || text == NULL)
    perror("malloc"), exit(EXIT_FAILURE);
  memcpy(text, plaintext, plaintextsize);
  ksa(S, key, keysize);
  prga(S, K, keystreamsize);
  rc4crypt(text, K, keystreamsize);
  if (memcmp(text, expect, plaintextsize)) {
    fprintf(stderr, "Test rc4crypt failed.\n");
    goto clean;
  }
  rc4decrypt(text, K, keystreamsize);
  if (memcmp(text, plaintext, plaintextsize)) {
    fprintf(stderr, "Test rc4decrypt failed.\n");
    goto clean;
  }
  printf("Test: OK\n");
clean:
  free(K);
  free(text);
}
int
main()
{
  const char * key = "Key", * plaintext = "Plaintext", * expect = "\xBB\xF3\x16\xE8\xD9\x40\xAF\x0A\xD3";
  test(plaintext, key, expect);
  
  return 0;
}

