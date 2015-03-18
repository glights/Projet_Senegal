
#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#ifndef CLASS_CAPTEURS_H
#define CLASS_CAPTEURS_H

class class_capteurs
{
public:

    // initialisation des capteurs
    void begin(void);

    // fonction pour prendre le courant à la batterie
    float getCurrent(void);

    // fonction pour prendre la tension
    float getVoltage(void);


private:
    // fonction pour lire
     uint16_t readADC(uint8_t ADCchannel);
};

#endif // CLASS_CAPTEURS_H
