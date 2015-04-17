// file: courantTension.cpp
/*
*	auteur: Guillaume & Ilalio
*	verison: 1
*
*/

//includes

#include "class_capteurs.h"

OneWire oneWire(9);

DallasTemperature tempSensors(&oneWire);

DeviceAddress tempDeviceAddress;

int numberOfDevices = 0;

bool class_capteurs::begin(void)
{
    // Select Vref=AVcc
    ADMUX |= (1<<REFS0);
    //set prescaller to 128 and enable ADC
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);

    tempSensors.begin();
    numberOfDevices = tempSensors.getDeviceCount();
    tempSensors.setResolution(PRECISION);
    if(tempSensors.getResolution() != PRECISION)
        return 1;
    else
        return 0;
}
//fonction pour prendre une mesure de courant a la batterie
float class_capteurs::getCurrent(void)
{
    return readADC(4)/10.24;
}

//fonction pour prendre une mesure de tension a la batterie
float class_capteurs::getVoltage(void)
{
    return readADC(5)/32.3333;
}
float class_capteurs::getTempAmbi(void)
{
    tempSensors.requestTemperatures();
    if(tempSensors.getAddress(tempDeviceAddress,TEMPAMBI))
    {
        return tempSensors.getTempC(tempDeviceAddress);
    }
    /*else if(!tempSensors.isConnected(tempDeviceAddress))
    {
        tempSensors.begin();
    }
    else return -1;*/
    //return tempSensors.getTempCByIndex(TEMPAMBI);
}

// fonction pour prendre la valeurs de temperature du moteur1
float class_capteurs::getTempMoteur1(void)
{
    tempSensors.requestTemperatures();
    if(tempSensors.getAddress(tempDeviceAddress,TEMPMOT1))
    {
        return tempSensors.getTempC(tempDeviceAddress);
    }
    //return tempSensors.getTempCByIndex(TEMPMOT1);
}

// fonction pour prendre la valeurs de temperature du moteur2
float class_capteurs::getTempMoteur2(void)
{
    tempSensors.requestTemperatures();
    if(tempSensors.getAddress(tempDeviceAddress,TEMPMOT2))
    {
        return tempSensors.getTempC(tempDeviceAddress);
    }
    //return tempSensors.getTempCByIndex(TEMPMOT2);
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

