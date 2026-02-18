#include <stdio.h>
#include <string.h>
#include <time.h>
#include "records.h"

void render(SetRecord *records, int count) {
  // ANSI code to clear screen
  printf("\033[H\033[J");

  // compute summary stats
  int jordan_wins = 0;
  int nick_wins = 0;
  for (int i = 0; i < count; i++) {
    if (strcmp(records[i].winner, "Jordan") == 0) {
      jordan_wins++;
    } else if (strcmp(records[i].winner, "Nick") == 0) {
      nick_wins++;
    } else {
      return;
    }
  }

  printf("=== DART BOARD ===\n");
  printf("Jordan: %d | Nick: %d | Total Games: %d\n", jordan_wins, nick_wins, count);
  printf("=======================================\n\n");
  
  printf("%-12s %-10s %-8s %-8s %-8s %s\n", "DATE", "WINNER", "SET 1", "SET 2", "SET 3", "NOTES");

  for (int i = 0; i < count; i++) {
    printf("%s | %s won | sets: %s %s %s\n",
      records[i].date,
      records[i].winner,
      records[i].set_one,
      records[i].set_two,
      records[i].set_three);
    printf("   notes: %s \n\n", records[i].notes);
  }

  printf("\n[n] new game [q] quit\n");
}


// returns an integer and accepts nothing - also the entry point of the application
int main(void) {
  SetRecord buf[MAX_RECORDS];
  int count = 0;
  load_records(buf, &count, MAX_RECORDS);

  while (1) {
    render(buf, count);

    int ch = getchar();
    while (getchar() != '\n');

    if (ch == 'q') {
      break;
    }

    if (ch == 'n') {
      SetRecord r;
      memset(&r, 0, sizeof(SetRecord));

      time_t t = time(NULL);
      struct tm *tm = localtime(&t);
      strftime(r.date, sizeof(r.date), "%Y-%m-%d", tm);

      printf("set 1: ");
      fgets(r.set_one, sizeof(r.set_one), stdin);
      r.set_one[strcspn(r.set_one, "\n")] = 0;

      printf("set 2: ");
      fgets(r.set_two, sizeof(r.set_two), stdin);
      r.set_two[strcspn(r.set_two, "\n")] = 0;

      printf("set 3: ");
      fgets(r.set_three, sizeof(r.set_three), stdin);
      r.set_three[strcspn(r.set_three, "\n")] = 0;

      printf("winner: ");
      fgets(r.winner, sizeof(r.winner), stdin);
      r.winner[strcspn(r.winner, "\n")] = 0;

      printf("notes: ");
      fgets(r.notes, sizeof(r.notes), stdin);
      r.notes[strcspn(r.notes, "\n")] = 0;

    append_record(&r);

      if (count < MAX_RECORDS) {
        buf[count] = r;
        count++;
      }
    }
  }

  printf("\033[H\033[J");
  return 0;
}
