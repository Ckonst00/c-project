#include "project.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// TODO:: implement your project here!
// ORDER THE LIST IN RIGHT ORDER!!!!!!!!!!!!!!
int compare(const void *a, const void *b) {
  Reservation *r1 = (Reservation *)a;
  Reservation *r2 = (Reservation *)b;

  if (r1->month != r2->month)
    return r1->month - r2->month;

  if (r1->day != r2->day)
    return r1->day - r2->day;

  return r1->hour - r2->hour;
}

int addReservation(char* buffer, Reservation** reservations, int* size) {
  char* args = buffer + 2;
  char name[50];
  int month, day, hour;


  if (sscanf(args, "%49s %d %d %d", name, &month, &day, &hour) != 4) {
    printf("Invalid command %s\n", args);
    return 0;
  }

  if (month < 1 || month > 12) {
    printf("Invalid command %d\n", month);
    return 0;
  }

  if (day > 31 || day < 1) {
    //printf("Invalid command %d\n", day);
    printf("Day cannot be less than 1 or greater than 31.\n");
    return 0;
  }

  if (hour > 24 || hour < 0) {
    printf("Invalid command %d\n", hour);
    return 0;
  }

  for (int i = 0; i < *size; i++) {
    if ((*reservations)[i].month == month && (*reservations)[i].day == day && (*reservations)[i].hour == hour) {
      return 0;
    }
  }

  *reservations = realloc(*reservations, (*size + 1) * sizeof(Reservation));
  if (!*reservations) {
    perror("Memory allocation fail");
    exit(1);
  }

  Reservation* new = &(*reservations)[*size];
  strcpy(new->name, name);
  new->month = month;
  new->day = day;
  new->hour = hour;

  (*size)++;
  return 1;
}



int deleteReservation(Reservation** reservations, int* size, char* buffer) {
  char* args = buffer + 2;
  int month, day, hour;

  int exist = 0;

  if (sscanf(args, "%d %d %d", &month, &day, &hour) != 3) {
    printf("Invalid command.\n");
    return 0;
  };


  for (int i = 0; i < *size; i++) {

    if ((*reservations)[i].month == month && (*reservations)[i].day == day && (*reservations)[i].hour == hour) {

      exist = 1;
      for (int j = i; j < *size - 1; j++) {
        (*reservations)[j] = (*reservations)[j + 1];
      }

      *reservations = realloc(*reservations, (*size - 1) * sizeof(Reservation));
      if (*reservations == NULL && *size > 1) {
        perror("Memory allocation fail");
        return 0;
      }

      (*size)--;
      break;
    }
  }

  if (exist == 0) {
    printf("The time slot %02d.%02d at %02d is not in the calendar.\n", day, month, hour);
    return 0;
  }
  return 1;
}

int listReservations(Reservation* reservations, int size) {

  if (reservations == NULL) {
    return 0;
  }

  qsort(reservations, size, sizeof(Reservation), compare);
  for (int i = 0; i < size; i++) {
    printf("%s %02d.%02d at %02d\n",
           reservations[i].name,
           reservations[i].day,
           reservations[i].month,
           reservations[i].hour);
  }
  return 1;
}

int saveToFile(Reservation* reservations, int size, char* buffer) {
  FILE *f;
  buffer = buffer + 2;
  char filename[100];
  sscanf(buffer, "%s", filename);


  f = fopen(filename, "w");
  if (f == NULL) {
    perror("File open failed");
    return 0;
  }

  for (int i = 0; i < size; i++) {
    fprintf(f, "%s %02d.%02d at %02d\n", reservations[i].name, reservations[i].day,
            reservations[i].month, reservations[i].hour);
  }

  fclose(f);
  return 1;
}

int loadReservations(char* buffer) {

  FILE *f2;
  buffer = buffer + 2;
  char filename[100];
  sscanf(buffer, "%s", filename);

  f2 = fopen(filename, "r");
  if (f2 == NULL) {
    perror("File open failed");
    return 0;
  }

  fclose(f2);
  return 1;
}

int main(void) {

  int size = 0;
  Reservation* reservations = NULL;
  char buffer[1000];

  while (1) {
    fgets(buffer, sizeof(buffer), stdin);

    if (buffer[0] == 'Q') {
      printf("SUCCESS\n");
      break;
    }
    switch (buffer[0]) {

      case 'A':
        if (addReservation(buffer, &reservations, &size)) {
          printf("SUCCESS\n");
        };
        break;

      case 'D':
        if (deleteReservation(&reservations, &size, buffer)) {
            printf("SUCCESS\n");
        };
        break;

      case 'L':
        if (listReservations(reservations, size)) {
            printf("SUCCESS\n");
        };
        break;

      case 'W':
        if (saveToFile(reservations, size, buffer)) {
          printf("SUCCESS\n");
        };
        break;

      case 'O':
        if (loadReservations(buffer)) {
          printf("SUCCESS\n");
        };
        break;

      default:
        printf("Invalid command\n");
        break;
    }
  }
  free(reservations);
  return 0;
}
