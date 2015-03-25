// file: courantTension.cpp
/*
*	auteur: Guillaume & Ilalio
*	verison: 1
*
*/

//includes

#include "class_capteurs.h"



void class_capteurs::begin(void)
{
    // Select Vref=AVcc
    ADMUX |= (1<<REFS0);
    //set prescaller to 128 and enable ADC
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);

    sensors.begin();
    numberOfDevices = sensors.getDeviceCount();

}
//fonction pour prendre une mesure de courant a la batterie
float class_capteurs::getCurrent(void)
{
    return readADC(4);
}

//fonction pour prendre une mesure de tension a la batterie
float class_capteurs::getVoltage(void)
{
    return readADC(5);
}
float getTempAmbi(void)
{
    return sensors.getTempCByIndex(TEMPAMBI);
}

// fonction pour prendre la valeurs de temperature du moteur1
float getTempMoteur1(void)
{
    return sensors.getTempC(TEMPMOT1);
}

// fonction pour prendre la valeurs de temperature du moteur2
float getTempMoteur2(void)
{
    return sensors.getTempC(TEMPMOT2);
}

//fonction pour prendre la date
String getDate(void)
{

}

uint16_t class_capteurs::readADC(uint8_t ADCchannel)
{
 //select ADC channel with safety mask
 ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
 //single conversion mode
 ADCSRA |= (1<<ADSC);
 // wait until ADC conversion is complete
 while( ADCSRA & (1<<ADSC) );

 return ADC;
}

