#include <TimerOne.h>

#include <classe_date.h>

#include <class_capteurs.h>
/*
*  Auteur : Guillaume Baril  & ilalio
* 
*
**/

class_capteurs capteurs;
Classe_date temp;
String date;

void setup(void)
{
  Serial.begin(9600);
  if(capteurs.begin())
    Serial.println("erreur");
  temp.setHeure(3,24,27);
  temp.setDate(2016,3,27);
  Timer1.initialize(1000000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}

void loop(void)
{
  Serial.print("DATE: ");
  Serial.println(temp.getDate());
  delay(200);
}

void timerIsr()
{
  //Serial.println(temp.getDate());
  //Serial.println(temp.j);
  //temp.incremanteTemp();
  temp.incremanteTemp();
}
