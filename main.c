#include <stdio.h>
#include <string.h>
#include "records.h"

int test() {
  printf("Running: test_append_and_load...");

  // declare r of type SetRecord
  SetRecord r;

  // clear any memory prior to starting
  memset(&r, 0, sizeof(SetRecord));

  // test date
  strncpy(r.date, "2026-02-17", sizeof(r.date) - 1);

  // test game  
  strncpy(r.game_one, "Jordan", sizeof(r.game_one) - 1);
  strncpy(r.game_two, "Nick", sizeof(r.game_two) - 1);
  strncpy(r.game_three, "Jordan", sizeof(r.game_three) - 1);
  strncpy(r.winner, "Jordan", sizeof(r.winner) - 1);
  strncpy(r.notes, "You bested me once again ole pal", sizeof(r.notes) - 1);

  // action - append it to the record
  append_record(&r);

  // check that it worked
  // declare variable buf of type SetRecord with max size of MAX_RECORDS
  SetRecord buf[MAX_RECORDS]

  // declare and set count to 0
  int count = 0;

  // load records passing the empty buf, memory address of count, and max records buf can accept 
  load_records(buf, &count, MAX_RECORDS);

  if (count > 0) {
    printf("pass - count: %d\n", count);
    return 1; // success
  } else {
    printf("fail - no records found\n")
      return 0;
  }
}

// returns an integer and accepts nothing - also the entry point of the application
int main(void) {
  int tests_passed = 0;

  if (test()) {
    tests_passed++;
  }

}
