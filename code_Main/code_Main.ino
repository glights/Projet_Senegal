#include <classe_sim908.h>
#include <SPI.h>
#include <SD.h>
#include <TimerOne.h>
#include <class_capteurs.h>
#include <classe_date.h>

File myfile;
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

String sDate = "2015-04-22 14:13:27";
unsigned char tensionBatterie = 0;
unsigned char ampBatterie = 0;
unsigned char tempAmbiante = 0;
unsigned char tempMoteur1 = 0;
unsigned char tempMoteur2 = 0;

char cDateFichier[13] = "20150423.txt";

int count = 0;

void setup() {
  pinMode(8,OUTPUT);
  pinMode(10, OUTPUT);
  SD.begin(4);
  Serial.begin(9600);
  capteurs.begin();
  date.setDate(2015,4,23);
  date.setHeure(23,59,26);
  delay(1000);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(timer1_isr);
}

void loop() {
  if(count >= 10)
  {
    count = 0;
    sDate = date.getDateComplete();
    //Serial.println();
    //Serial.print("date: ");
    //Serial.println(sDate);
    ampBatterie = capteurs.getCurrent();
   // Serial.print("courant: ");
   // Serial.println(ampBatterie);
    tensionBatterie = capteurs.getVoltage();
   // Serial.print("tension: ");
   // Serial.println(tensionBatterie);
    tempAmbiante = capteurs.getTempAmbi();
   // Serial.print("temperature Ambiante: ");
   // Serial.println(tempAmbiante);
    tempMoteur1 = capteurs.getTempMoteur1();
   // Serial.print("temperature Moteur1: ");
   // Serial.println(tempMoteur1);
    tempMoteur2 = capteurs.getTempMoteur2();
   // Serial.print("temperature Moteur2: ");
   // Serial.println(tempMoteur2);
    
    ecritureSD();
  }
    
}

void ecritureSD(void)
{
  char myChar;
  int k;
  char *p_cDateFichier;
  char cOldDateFichier[13] = "20150423.txt";
  boolean nouveauFichier = false;
  boolean finFichier = false;
 
  for(k = 0; k<13; k++)
  {
    cOldDateFichier[k] = cDateFichier[k];
  }
  
  p_cDateFichier = date.getDateFichier();
  // lecture de la date
  for(k=0; k<13;k++)
  {
    cDateFichier[k] = p_cDateFichier[k];
  }
  
   if(!SD.exists(cDateFichier))
  {
      nouveauFichier = true;
  }
  
  if((date.temp.heure == 23)&&(date.temp.minute == 59)&&(date.temp.seconde >= 50))
    finFichier = true;
  
  myfile = SD.open(cDateFichier, FILE_WRITE);
  
  if(nouveauFichier)
  {
    nouveauFichier = false;
    for (k = 0; k < strlen(debut); k++)
    {
      myChar =  pgm_read_byte_near(debut + k);
      myfile.print(myChar);
    }
    
    myfile.print(sDate);
    
    for (k = 0; k < strlen(debut2); k++)
    {
      myChar =  pgm_read_byte_near(debut2 + k);
      myfile.print(myChar);
    }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  for (k = 0; k < strlen(charProgId); k++)
    {
      myChar =  pgm_read_byte_near(charProgId + k);
      myfile.print(myChar);
    }
    myfile.print("1");
    
    for (k = 0; k < strlen(charProgDateTime); k++)
    {
      myChar =  pgm_read_byte_near(charProgDateTime + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(ampBatterie,DEC);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    
    ////////////////////////////////////////////////////////////////
    for (k = 0; k < strlen(charProgId); k++)
    {
      myChar =  pgm_read_byte_near(charProgId + k);
      myfile.print(myChar);
    }
    myfile.print("2");
    
    for (k = 0; k < strlen(charProgDateTime); k++)
    {
      myChar =  pgm_read_byte_near(charProgDateTime + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(tensionBatterie,DEC);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    
    ////////////////////////////////////////////////////////////////
    for (k = 0; k < strlen(charProgId); k++)
    {
      myChar =  pgm_read_byte_near(charProgId + k);
      myfile.print(myChar);
    }
    myfile.print("3");
    
    for (k = 0; k < strlen(charProgDateTime); k++)
    {
      myChar =  pgm_read_byte_near(charProgDateTime + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(tempAmbiante,DEC);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    
    //////////////////////////////////////////////////////////////
    for (k = 0; k < strlen(charProgId); k++)
    {
      myChar =  pgm_read_byte_near(charProgId + k);
      myfile.print(myChar);
    }
    myfile.print("4");
    
    for (k = 0; k < strlen(charProgDateTime); k++)
    {
      myChar =  pgm_read_byte_near(charProgDateTime + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(tempMoteur1,DEC);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    
    /////////////////////////////////////////////////////////////
    for (k = 0; k < strlen(charProgId); k++)
    {
      myChar =  pgm_read_byte_near(charProgId + k);
      myfile.print(myChar);
    }
    myfile.print("5");
    
    for (k = 0; k < strlen(charProgDateTime); k++)
    {
      myChar =  pgm_read_byte_near(charProgDateTime + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(tempMoteur2,DEC);
    
    /*for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }*/
    //////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // ferme le fichier Json
  if(finFichier)
  {
    finFichier = false;
    for (k = 0; k < strlen(fin); k++)
    {
      myChar =  pgm_read_byte_near(fin + k);
      myfile.print(myChar);
    }
    myfile.close();
    EnvoieDonne(cOldDateFichier);
  }
  else
  {
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    myfile.close();
  }
}


void EnvoieDonne(char envoieFichier[13])
{
  myfile = SD.open(envoieFichier);
  if(myfile)
  {
    delay(500);
    sim908.power_onSim();
    delay(15000);
    sim908.setSim908();
    delay(1000);
    
    sim908.envoieJson(myfile.size());
    delay(100);
    while (myfile.available()) {
        Serial.write(myfile.read());
      }
    delay(20000);
    sim908.sendJson();
    sim908.power_offSim();
  }
}

/************************************/
// interupt timer 1
void timer1_isr(void)
{
  count++;
  date.incremanteTemp();
}
/***********************************/
