#include "consigne.h"

float consigne(float csgn)
{
  if (access(CONSIGNE_LOCK_PATH, F_OK) != -1)
  { // Check if the lock exist
    fprintf(stderr, "File %s is locked !", CONSIGNE_PATH);
  }
  else
  {
    FILE *sum_file_pointer = NULL;
    FILE *lock = fopen(CONSIGNE_LOCK_PATH, "w"); // Create a lock

    if (access(CONSIGNE_PATH, F_OK) == -1) {
      sum_file_pointer = fopen(CONSIGNE_PATH, "w+"); // Create the consigne file
      fputs("0\n", sum_file_pointer);

      fclose(sum_file_pointer);
    } 

    sum_file_pointer = fopen(CONSIGNE_PATH, "r"); // Open the consigne file

    if (!sum_file_pointer)  // Check if open is successfull
    {
      fprintf(stderr, "Failed to open %s !\n", CONSIGNE_PATH);

      free(lock);
      remove(CONSIGNE_LOCK_PATH);

      return csgn;
    }

    char str_pui[MAX_BUFFER_SIZE] = {0}; // target temperature string
    if (!fgets(str_pui, MAX_BUFFER_SIZE,
               sum_file_pointer))
    {
      fprintf(stderr, "Failed to read on %s !\n", CONSIGNE_PATH); // Read Failed
    }
    csgn = atof(str_pui); // Convert target temperature string to float

    fclose(sum_file_pointer); // Delete file pointer
    fclose(lock);             // Delete file pointer

    remove(CONSIGNE_LOCK_PATH); // Lock removed
  }

  return csgn;
}
