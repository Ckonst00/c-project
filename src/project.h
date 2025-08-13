#ifndef _PROJECT__H_
#define _PROJECT__H_

typedef struct {
    char name[50];
    int month;
    int day;
    int hour;
} Reservation;

int compare(const void *a, const void *b);

int addReservation(char* buffer, Reservation** reservations, int* size);

int listReservations(Reservation* reservations, int size);

int deleteReservation(Reservation** reservations, int* size, char* buffer);

int saveToFile(Reservation* reservations, int size, char* buffer);

int loadReservations(char* buffer);


#endif //! _PROJECT__H_