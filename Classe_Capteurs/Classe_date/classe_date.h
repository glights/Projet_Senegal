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
        int m = 3;
        int d = 27;
    };

    int dOffset = 0;

    struct sTemp
    {
        int heure = 23;
        int minute = 55;
        int seconde = 58;
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
