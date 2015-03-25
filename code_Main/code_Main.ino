#include <DallasTemperature.h>

#include <OneWire.h>

#include <class_capteurs.h>

/*
*  Auteur : Guillaume Baril  & ilalio
* 
*
**/

class_capteurs capteurTC;


void setup(void)
{
  Serial.begin(9600);
  capteurTC.begin();
}

void loop(void)
{
  Serial.print("valeur:");
  Serial.println(capteurTC.getCurrent());
  delay(1000);
}
