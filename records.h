#ifndef RECORDS_H
#define RECORDS_H

#define MAX_NOTES 256
#define MAX_NAME 32
#define MAX_RECORDS 128
#define RECORDS_FILE "darts.dat"

typedef struct {
  char date[16];
  char set_one[MAX_NAME];
  char set_two[MAX_NAME];
  char set_three[MAX_NAME];
  char winner[MAX_NAME];
  char notes[MAX_NOTES];
} SetRecord;

void load_records(SetRecord *buf, int *count, int max);
void append_record(const SetRecord *r);

#endif
