#include <classe_sim908.h>
#include <SD.h> 
#include <SPI.h>
#include <TimerOne.h>
#include <classe_date.h>
#include <class_capteurs.h>

File myfile;
class_capteurs capteurs;
Classe_date date;
classe_sim908 sim908;

const  char debut[] PROGMEM = "{\"stationmessage\":{\"datetime\":\"";
const char debut2[] PROGMEM= "\",\"stationid\":\"sen002\",\"eventtype\":\"regularreading\",\"event\":[{\"sensorunit\":\"su0009\",\"data\":[";
const char charProgId[] PROGMEM = "{\"id\":\"0";
const char charProgDateTime[] PROGMEM = "\",\"datetime\":\"";
const char charProgValueType[] PROGMEM = "\",\"valuetype\":\"asis\",\"value\":\"";
const char charProgEndValue[] PROGMEM = "\"},";
const char fin[] PROGMEM = "\"}]}]}}";

String sDate = "2015-04-17 09:23:27";
int tensionBatterie = 0;
int ampBatterie = 0;
//float tempAmbiante = 0;
int tempMoteur1 = 0;
int tempMoteur2 = 0;
//double vitesseMoteur = 0;
boolean alarmeVib = false;

char cDateFichier[13];

int vitesseHz = 0;

int count = 0;

boolean nouveauFichier = false;
boolean finFichier = false;

void setup (void)
{
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  Timer1.initialize(1000000);
  //Serial.println("\n\rstarting...");
  capteurs.begin();
  Timer1.attachInterrupt(timer1_isr);
 // attachInterrupt(0, vitesse, FALLING);
  attachInterrupt(1, intAlarme, FALLING);
  date.setDate(2015,4,2);
  date.setHeure(23,59,22);
  if (!SD.begin(4)) {
    //Serial.println("initialization SD failed!");
  }
  //Serial.println("initialization SD done.");
  delay(5000);
}

void loop(void)
{  
  if(count >= 10)
  {
    //Serial.println("ok");
    count = 0;
    if(isMotorOn())
    {
        sDate = date.getDateComplete();
        //Serial.println();
        //Serial.print("date: ");
        //Serial.println(sDate);
        ampBatterie = capteurs.getCurrent();
        //Serial.print("courant: ");
        //Serial.println(ampBatterie);
        tensionBatterie = capteurs.getVoltage();
        //Serial.print("tension: ");
        //Serial.println(tensionBatterie);
        //tempAmbiante = capteurs.getTempAmbi();
        //Serial.print("temperature Ambiante: ");
        //Serial.println(tempAmbiante);
        tempMoteur1 = capteurs.getTempMoteur1();
        //Serial.print("temperature Moteur1: ");
        //Serial.println(tempMoteur1);
        tempMoteur2 = capteurs.getTempMoteur2();
        //Serial.print("temperature Moteur2: ");
        //Serial.println(tempMoteur2);
        //Serial.print("vitesse du moteur");
        //Serial.println(vitesseMoteur);
        //Serial.print("etat Alarme moteur:");
        /*if(alarmeVib)
        {
          Serial.println("true");
        }
        else
          Serial.println("false");
        */
        ecritureSD();
        alarmeVib = false;
    }
  }
}

void ecritureSD(void)
{
  char myChar;
  int k;
  int i;
  char *p_cDateFichier;
  
  p_cDateFichier = date.getDateFichier();
  
  for(i=0; i<=13;i++)
  {
    cDateFichier[i] = p_cDateFichier[i];
  }
  
  // si fichier existe pas creer un nouveau fichier
  if(!SD.exists(cDateFichier))
      nouveauFichier = true;
      
  if((date.temp.heure == 23)&&(date.temp.minute == 59)&&(date.temp.seconde >= 50))
    finFichier= true;
  
  myfile = SD.open(cDateFichier, FILE_WRITE);
  // ouvre le fichier Json
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
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    myfile.print(ampBatterie);
    
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
    myfile.print(tensionBatterie);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    
    ////////////////////////////////////////////////////////////////
    /*for (k = 0; k < strlen(charProgId); k++)
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
    myfile.print(tempAmbiante);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }*/
    
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
    myfile.print(tempMoteur1);
    
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
    myfile.print(tempMoteur2);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    /////////////////////////////////////////////////////////////
    /*for (k = 0; k < strlen(charProgId); k++)
    {
      myChar =  pgm_read_byte_near(charProgId + k);
      myfile.print(myChar);
    }
    myfile.print("6");
    
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
    myfile.print(vitesseMoteur);
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }*/
    
    ///////////////////////////////////////////////////////////////
    for (k = 0; k < strlen(charProgId); k++)
    {
      myChar =  pgm_read_byte_near(charProgId + k);
      myfile.print(myChar);
    }
    myfile.print("7");
    
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
    if(alarmeVib)
        {
          myfile.print("true");
        }
        else
          myfile.print("false");
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  // ferme le fichier Json
  if(finFichier)
  {
    finFichier = false;
    //finFichier = true;
    for (k = 0; k < strlen(fin); k++)
    {
      myChar =  pgm_read_byte_near(fin + k);
      myfile.print(myChar);
    }
    myfile.close();
  // EnvoieDonne();
  }
  else
  {
  for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
  }
  
 // Serial.println("done.");

  //pinMode(10, INPUT);
}
boolean isMotorOn(void)
{
  if(tensionBatterie >= 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void EnvoieDonne(void)
{
  /*myfile = SD.open("ALLO.txt");
  delay(500);
  sim908.power_onSim();
  sim908.setSim908();
  delay(1000);
  sim908.envoieJson(myfile.size());
  delay(100);
  while (myfile.available()) {
      Serial.write(myfile.read());
    }
  delay(5000);
  sim908.sendJson();
  sim908.power_offSim();*/
}

void vitesse(void)
{
  vitesseHz++;
}

void intAlarme(void)
{
  alarmeVib = true;
}

void timer1_isr(void)
{
  //vitesseMoteur = vitesseHz*60;
  //vitesseHz = 0;
  count++;
  date.incremanteTemp();
}

void Sim900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  delay(5000);
}

