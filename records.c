#include <stdio.h>
#include <string.h>
#include "records.h"

// stdio.h gives access to fopen, fwrite, fread, fclose
// string.h gives access to memset which we will use to zero out memory cleanly
// records.h gives access to the RECORDS_FILE definition, SetRecord struct, and function signatures

// has no return type and accepts a pointer to a SetRecord struct
void append_record(const SetRecord *r) {
  
  // FILE is a struct defined in stdio.h and we will decleare a pointer to it with *f 
  // fopen takes a path and mode string - in this case we are passing "ab" for append, binary
  FILE *f = fopen(RECORDS_FILE, "ab");

  // if the file is NULL, we will throw an error that also spits out the file system error and an empty return
  if (f == NULL) {
    perror("Failed to open records file");
    return;
  }
  
  // fwrite takes the r pointer from the signature, size of the struct, number of elements, and the f pointer
  fwrite(r, sizeof(SetRecord), 1, f);

  // always call this or else your data will live in a memory buffer forever
  fclose(f);
}


// has no return type and accepts a pointer *buf with type SetRecord, pointer to count, and max
void load_records(SetRecord *buf, int *count, int max) {
  
  // declare pointer to count variable with type taken from function signature
  *count = 0;

  // same as above, expect we will read, binary and not error if the file is empty
  FILE *f = fopen(RECORDS_FILE, "rb");
  if (f == NULL) {
    return;
  }

  // reads one record at a time and checks if pointer to count is less than max
  while (*count < max) {

    // declares local variable and sets it to what it can read from that buf's memory location and count index 
    // the rest of fread then sets the size of the struct, how many there are, and the file pointer
    int result = fread(&buf[*count], sizeof(SetRecord), 1, f);

    // if we don't get one kill it
    if (result != 1) {
      break;
    }

    // apparently C hates us and if we don't use () the pointer will be incremented instead of the value
    (*count)++;
  }

  // close that file boi!!
  fclose(f);
}

