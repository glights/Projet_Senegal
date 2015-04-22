#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#include <inttypes.h>
#include "Arduino.h"
#include "TimerOne.h"

#ifndef CLASSE_DATE_H
#define CLASSE_DATE_H

class Classe_date
{
public:
    struct sDate
    {
        int y = 2015;
        unsigned char m = 3;
        unsigned char d = 27;
    };

    int dOffset = 0;

    struct sTemp
    {
        unsigned char heure = 23;
        unsigned char minute = 55;
        unsigned char seconde = 58;
    };

    struct sDate date;
    struct sTemp temp;

    long j = 0;

    long gday(void);

    void incremanteDate (void);

    void incremanteTemp(void);

    //fonction pour prendre la date
    char *getDateComplete(void);

    char *getDate(void);

    char *getDateFichier(void);

    char *getHeure(void);

    void setDate(long y, long m, long d);

    void setHeure(int h, int m, int s);
};

#endif // CLASSE_DATE_H
