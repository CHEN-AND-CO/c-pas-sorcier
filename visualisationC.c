#include "visualisationC.h"

void visualisationC(float puissance_f) {
  if (access(DATA_LOCK_PATH, F_OK) != -1) // Check if the lock exist
  {
    fprintf(stderr, "File %s is locked !", DATA_PATH);
  } else {
    FILE *lock = fopen(DATA_LOCK_PATH, "w"); // Create the access lock
    FILE *sum_file_pointer = NULL;

    if (access(DATA_PATH, F_OK) == -1) {
      sum_file_pointer = fopen(DATA_PATH, "w+"); // Create the data file
      fputs("0.0\n0.0\ntrue\n", sum_file_pointer);

      fclose(sum_file_pointer);
    } 

    #ifdef __linux__
      sum_file_pointer = fopen(DATA_PATH, "r+"); // Open the data file
    #else
      sum_file_pointer = fopen(DATA_PATH, "a+"); // Open the data file
    #endif

    if (!sum_file_pointer) // Check if we somehow manage to not open it
    {
      fprintf(stderr, "Failed to open %s !\n", DATA_PATH);

      fclose(lock);           // Close the lock access
      remove(DATA_LOCK_PATH); // Remove the lock

      return;
    }

    char *str_pui =
        malloc(MAX_BUFFER_SIZE * sizeof(char)); // Power command string
    if (puissance_f > 0) {
      str_pui = "true\n";
    } else {
      str_pui = "false\n";
    }

    /* This part allow us to set the write cursor to the 3rd line */
    char *tmp = malloc(MAX_BUFFER_SIZE * sizeof(char));
    rewind(sum_file_pointer); // Set the cursor to the beginning of the file
    tmp = fgets(tmp, MAX_BUFFER_SIZE, sum_file_pointer); // Jump to the 1st line
    tmp = fgets(tmp, MAX_BUFFER_SIZE, sum_file_pointer); // Jump to the 2nd line
    if (tmp) {
      free(tmp); // Remove tmp from the memory
    }

    if (fputs(str_pui, sum_file_pointer) == -1) // Write failed
    {
      fprintf(stderr, "Failed to write on %s !\n", DATA_PATH);
    }

    fclose(sum_file_pointer); // Delete the file pointer
    fclose(lock);             // Delete the file pointer

    remove(DATA_LOCK_PATH); // Remove the lock
  }
}
