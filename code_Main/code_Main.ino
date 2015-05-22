#include <classe_sim908.h>
#include <SPI.h>
#include <SD.h>
#include <TimerOne.h>
#include <class_capteurs.h>
#include <classe_date.h>
#include <EEPROM.h>

File myFile;
class_capteurs capteurs;
Classe_date date;
classe_sim908 sim908;

const char debut[] PROGMEM = "data={\"stationmessage\":{\"datetime\":\"";
const char debut2[] PROGMEM = "\",\"stationid\":\"sen002\",\"eventtype\":\"regularreading\",\"event\":[{\"sensorunit\": \"su0009\",\"data\": [";
const char charProgId[] PROGMEM = "{\"id\":\"0";
const char charProgDateTime[] PROGMEM = "\",\"datetime\":\"";
const char charProgValueType[] PROGMEM = "\",\"valuetype\":\"asis\",\"value\":\"";
const char charProgEndValue[] PROGMEM = "\"},";
const char fin[] PROGMEM = "\"}]}]}}";


const char sdDebutFin[] PROGMEM = "***********************************************\n\r";
const char sdDate[] PROGMEM = "Date: ";
const char sdCourant[] PROGMEM = "Courant batterie: ";
const char sdTension[] PROGMEM = "Tension batterie: ";
const char sdTemp1[] PROGMEM = "Temperature ambiante: ";
const char sdTemp2[] PROGMEM = "Temperature moteur1: ";
const char sdTemp3[] PROGMEM = "Temperature moteur2: ";


String sDate = "2015-04-22 14:13:27";
float tensionBatterie = 0;
float ampBatterie = 0;
float tempAmbiante = 0;
float tempMoteur1 = 0;
float tempMoteur2 = 0;

char cDateFichier[13] = "20150423.txt";

int count = 0;

void setup() 
{
  pinMode(8,OUTPUT);
  pinMode(10, OUTPUT);
  SD.begin(4);
  Serial.begin(9600);
  capteurs.begin();
  date.setDate(EEPROM.read(0)+2000,EEPROM.read(1),EEPROM.read(2));
  date.setHeure(EEPROM.read(3),EEPROM.read(4),EEPROM.read(5));
  delay(1000);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timer1_isr);
  sim908.power_onSim();
  delay(5000);
  sim908.setSim908();
  
}

void loop() {
  
  if(count >= 15)
  {
    count = 0;
    
    tensionBatterie = capteurs.getVoltage();
    
    // vérifie si le moteur est allumé
    if(tensionBatterie >= 5)
    {
        //Serial.println("prise");
        sDate = date.getDateComplete();
        ampBatterie = capteurs.getCurrent();
        tempAmbiante = capteurs.getTempAmbi();
        tempMoteur1 = capteurs.getTempMoteur1();
        tempMoteur2 = capteurs.getTempMoteur2();
        ecritureSD();
        EnvoieDonne();
        
        SauvegardeDate();
    }
  }
  else if(count == 5)
  {
    sim908.power_onSim();
  }
}

void ecritureSD(void)
{
  char *p_cDateFichier;
  char cDateFichier[13];
  int k;
  
  p_cDateFichier = date.getDateFichier();
  
  for(k=0; k<13;k++)
  {
    cDateFichier[k] = p_cDateFichier[k];
  }
  
  myFile = SD.open(cDateFichier,FILE_WRITE);
  
  if(myFile)
  {
    //Serial.println("test");
    printProgmemSD(sdDebutFin);
    printProgmemSD(sdDate);
    myFile.println(sDate);
    myFile.println();
    printProgmemSD(sdCourant);
    myFile.println(ampBatterie);
    printProgmemSD(sdTension);
    myFile.println(tensionBatterie);
    printProgmemSD(sdTemp1);
    myFile.println(tempAmbiante);
    printProgmemSD(sdTemp2);
    myFile.println(tempMoteur1);
    printProgmemSD(sdTemp3);
    myFile.println(tempMoteur2);
    printProgmemSD(sdDebutFin);
    myFile.close();
  }
}

void EnvoieDonne(void)
{
  int nombreChar = 0;
  
  nombreChar = envoieJson();
  delay(1000);
  sim908.envoieJson(nombreChar);
  envoieJson();
  sim908.sendJson();
}

int envoieJson(void)
{
  int nombreChar = 0;
  nombreChar += printProgmem(debut);
  nombreChar += Serial.print(sDate);
  
  nombreChar += printProgmem(debut2);
  
  nombreChar += printProgmem(charProgId);
  nombreChar += Serial.print("1");
  
  nombreChar += printProgmem(charProgDateTime);
  nombreChar += Serial.print(sDate);
  
  nombreChar += printProgmem(charProgValueType);
  nombreChar += Serial.print(ampBatterie,2);

  nombreChar += printProgmem(charProgEndValue);
 
    
    ////////////////////////////////////////////////////////////////
  nombreChar += printProgmem(charProgId);
  nombreChar += Serial.print("2");
  
  nombreChar += printProgmem(charProgDateTime);
  nombreChar += Serial.print(sDate);
  
  nombreChar += printProgmem(charProgValueType);
  nombreChar += Serial.print(tensionBatterie,2);
  
  nombreChar += printProgmem(charProgEndValue);
    
    ////////////////////////////////////////////////////////////////

  nombreChar += printProgmem(charProgId);
  nombreChar += Serial.print("3");
    
  nombreChar += printProgmem(charProgDateTime);
  nombreChar += Serial.print(sDate);
  
  nombreChar += printProgmem(charProgValueType);
  nombreChar += Serial.print(tempAmbiante,2);
  
  nombreChar += printProgmem(charProgEndValue);
    
    //////////////////////////////////////////////////////////////
    
  nombreChar += printProgmem(charProgId);
  nombreChar += Serial.print("4");
  
  nombreChar += printProgmem(charProgDateTime);
  nombreChar += Serial.print(sDate);
  
  nombreChar += printProgmem(charProgValueType);
  nombreChar += Serial.print(tempMoteur1,2);
  
  nombreChar += printProgmem(charProgEndValue);
    
  /////////////////////////////////////////////////////////////
 
  nombreChar += printProgmem(charProgId);
  nombreChar += Serial.print("5");
    
  nombreChar += printProgmem(charProgDateTime);
  nombreChar += Serial.print(sDate);
 
  nombreChar += printProgmem(charProgValueType);
  nombreChar += Serial.print(tempMoteur2,2);
  
  ///////////////////////////
  nombreChar += printProgmem(fin);
  
  Serial.println();
  return nombreChar;
}

int printProgmem(const char charProg[])
{
  char myChar;
  int k;
  int nombreChar = 0;
  
  for (k = 0; myChar != '\0'; k++)
  {
    myChar =  pgm_read_byte_near(charProg + k);
    if(myChar != '\0')
      nombreChar += Serial.print(myChar);
  }
  return nombreChar;
}

void printProgmemSD(const char charProg[])
{
  char myChar;
  int k;
  
  for (k = 0; myChar != '\0'; k++)
  {
    myChar =  pgm_read_byte_near(charProg + k);
    if(myChar != '\0')
      myFile.print(myChar);
  }
}

void SauvegardeDate(void)
{
  EEPROM.write(0,date.dOffset-2000+date.date.y);
  EEPROM.write(1,date.date.m);
  EEPROM.write(2,date.date.d);
  EEPROM.write(3,date.temp.heure);
  EEPROM.write(4,date.temp.minute);
  EEPROM.write(5,date.temp.seconde);
}

/************************************/
// interupt timer 1
void timer1_isr(void)
{
  count++;
  date.incremanteTemp();
}
/***********************************/
