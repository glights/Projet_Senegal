
#include <stdio.h>
#include <avr/io.h>
#include <stdint.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#ifndef CLASS_CAPTEURS_H
#define CLASS_CAPTEURS_H

#define TEMPAMBI 0
#define TEMPMOT1 1
#define TEMPMOT2 2

OneWire oneWire(10);

DallasTemperature sensors(&oneWire);

int numberOfDevices = 0;


class class_capteurs
{
public:

    // initialisation des capteurs
    void begin(void);

    // fonction pour prendre le courant à la batterie
    float getCurrent(void);

    // fonction pour prendre la tension
    float getVoltage(void);

    // fonction pour prendre la valeur de temperature ambiante
    float getTempAmbi(void);

    // fonction pour prendre la valeurs de temperature du moteur1
    float getTempMoteur1(void);

    // fonction pour prendre la valeurs de temperature du moteur2
    float getTempMoteur2(void);

    //fonction pour prendre la date
    String getDate(void);

private:
    // fonction pour lire l'ADC
     uint16_t readADC(uint8_t ADCchannel);

     float getTemp(DeviceAddress adresse, int i);
};

#endif // CLASS_CAPTEURS_H
