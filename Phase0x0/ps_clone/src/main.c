#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  printf("[+] Process Enumerator [Loading...]\n");
  // check for proper arguments.
  if (argc < 2)
  {
    printf("usage: <./program> <option>\noptions:\n\t-l: to list processes\n[Exiting...]\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
