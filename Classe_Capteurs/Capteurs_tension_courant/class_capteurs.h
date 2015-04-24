
#include "DallasTemperature.h"
#ifndef CLASS_CAPTEURS_H
#define CLASS_CAPTEURS_H

#define TEMPAMBI 2
#define TEMPMOT1 1
#define TEMPMOT2 0

#define PRECISION 10

class class_capteurs
{
public:

    // initialisation des capteurs
    bool begin(void);

    // fonction pour prendre le courant à la batterie
    unsigned char getCurrent(void);

    // fonction pour prendre la tension
    unsigned char getVoltage(void);

    // fonction pour prendre la valeur de temperature ambiante
    unsigned char getTempAmbi(void);

    // fonction pour prendre la valeurs de temperature du moteur1
    unsigned char getTempMoteur1(void);

    // fonction pour prendre la valeurs de temperature du moteur2
    unsigned char getTempMoteur2(void);

    //fonction pour prendre la date
    String getDate(void);

private:
    // fonction pour lire l'ADC
     int readADC(uint8_t ADCchannel);

     void incremanteDate(void);
};

#endif // CLASS_CAPTEURS_H
