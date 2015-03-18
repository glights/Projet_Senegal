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
