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

<<<<<<< HEAD
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
=======
const PROGMEM char debut[] = "{\"stationmessage\":{\"datetime\":\"";
const PROGMEM char charProg1[] = "\",\"stationid\":\"sta001\",\"eventtype\":\"regularreading\",\"event\":[";
const PROGMEM char charProg2[] = "{\"sensorunit\":\"su0001\",\"data\":[{\"id\":\"01\",\"datetime\":\"";
const PROGMEM char charProgValueType[] = "\",\"valuetype\":\"asis\",\"value\":\"";
const PROGMEM char charProgId2[] = "\"},{\"id\":\"02\",\"datetime\":\"";
const PROGMEM char charProg6[] = "\"}]},{\"sensorunit\":\"su0002\",\"data\":[{\"id\":\"01\",\"datetime\":\"";
const PROGMEM char charProg7[] = "\"},{\"id\":\"03\",\"datetime\":\"";
const PROGMEM char charProg9[] = "\"}]},{\"sensorunit\":\"su0003\",\"data\":[{\"id\":\"01\",\"datetime\":\"";
const PROGMEM char charProgFinCap[] = "}]}";
const PROGMEM char fin[] = "]}}";

char *sDate = "    ";
float tensionBatterie = 55.45;
float ampBatterie = 60.3;
float tempAmbiante = 36.65;
float tempMoteur1 = 100.35;
float tempMoteur2 = 100.98;
double vitesseMoteur = 6000;
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
boolean alarmeVib = false;

char cDateFichier[13];

int vitesseHz = 0;

int count = 0;

boolean nouveauFichier = false;
boolean finFichier = false;

void setup (void)
{
  Serial.begin(9600);
  Timer1.initialize(1000000);
  //Serial.println("\n\rstarting...");
  capteurs.begin();
  Timer1.attachInterrupt(timer1_isr);
 // attachInterrupt(0, vitesse, FALLING);
  attachInterrupt(1, intAlarme, FALLING);
<<<<<<< HEAD
  date.setDate(2015,4,2);
  date.setHeure(23,59,22);
  if (!SD.begin(4)) {
    //Serial.println("initialization SD failed!");
  }
  //Serial.println("initialization SD done.");
=======
  //date.setDate(2015,4,2);
  //date.setHeure(16,24,33);
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
  delay(5000);
}

void loop(void)
{  
  if(count >= 10)
  {
    //Serial.println("ok");
    count = 0;
<<<<<<< HEAD
    if(isMotorOn())
    {
        sDate = date.getDateComplete();
        //Serial.println();
        //Serial.print("date: ");
        //Serial.println(sDate);
=======
    if(isMotorOn)
    {
        //sDate = date.getDateComplete();
        Serial.println();
        Serial.print("date: ");
        Serial.println(sDate);
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
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
<<<<<<< HEAD
        //Serial.print("temperature Moteur2: ");
        //Serial.println(tempMoteur2);
        //Serial.print("vitesse du moteur");
        //Serial.println(vitesseMoteur);
        //Serial.print("etat Alarme moteur:");
        /*if(alarmeVib)
=======
        Serial.print("temperature Moteur2: ");
        Serial.println(tempMoteur2);
        Serial.print("vitesse du moteur");
        Serial.println(vitesseMoteur);
        Serial.print("etat Alarme moteur:");
        if(alarmeVib)
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
        {
          Serial.println("true");
          alarmeVib = false;
        }
        else
          Serial.println("false");
<<<<<<< HEAD
        */
        ecritureSD();
        alarmeVib = false;
=======
          
        ecritureSD();
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    }
  }
}

void ecritureSD(void)
{
  char myChar;
  int k;
  int i;
  char *p_cDateFichier;
  
<<<<<<< HEAD
  p_cDateFichier = date.getDateFichier();
  
  for(i=0; i<=13;i++)
  {
    cDateFichier[i] = p_cDateFichier[i];
=======
  pinMode(10, OUTPUT);
  
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
  }
  
<<<<<<< HEAD
  // si fichier existe pas creer un nouveau fichier
  if(!SD.exists(cDateFichier))
      nouveauFichier = true;
      
  if((date.temp.heure == 23)&&(date.temp.minute == 59)&&(date.temp.seconde >= 50))
    finFichier= true;
  
  myfile = SD.open(cDateFichier, FILE_WRITE);
=======
  myfile = SD.open(date.getDateFichier(), FILE_WRITE);

>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
  // ouvre le fichier Json
  if(nouveauFichier)
  {
    nouveauFichier = false;
<<<<<<< HEAD
    for (k = 0; k < strlen(debut); k++)
=======

   for (k = 0; k < strlen(debut); k++)
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    {
      myChar =  pgm_read_byte_near(debut + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProg1); k++)
    {
      myChar =  pgm_read_byte_near(charProg1 + k);
      myfile.print(myChar);
    }
<<<<<<< HEAD
 }
=======
  }
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
  
  for (k = 0; k < strlen(charProg2); k++)
    {
      myChar =  pgm_read_byte_near(charProg2 + k);
      myfile.print(myChar);
    }
    
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    
    myfile.print(ampBatterie);
    
    for (k = 0; k < strlen(charProgId2); k++)
    {
      myChar =  pgm_read_byte_near(charProgId2 + k);
      myfile.print(myChar);
    }
    
    myfile.print(sDate);
    
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    
    myfile.print(tensionBatterie);
    
    for (k = 0; k < strlen(charProgFinCap); k++)
    {
      myChar =  pgm_read_byte_near(charProgFinCap + k);
      myfile.print(myChar);
    }
    
<<<<<<< HEAD
    ////////////////////////////////////////////////////////////////
    /*for (k = 0; k < strlen(charProgId); k++)
=======
    for (k = 0; k < strlen(charProg6); k++)
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    {
      myChar =  pgm_read_byte_near(charProg6 + k);
      myfile.print(myChar);
    }
    
    myfile.print(sDate);
    for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(tempAmbiante);
<<<<<<< HEAD
    
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }*/
    
    //////////////////////////////////////////////////////////////
    for (k = 0; k < strlen(charProgId); k++)
=======
     for (k = 0; k < strlen(charProgId2); k++)
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    {
      myChar =  pgm_read_byte_near(charProgId2 + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
     for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(tempMoteur1);
     for (k = 0; k < strlen(charProg7); k++)
    {
      myChar =  pgm_read_byte_near(charProg7 + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
     for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(tempMoteur2);
    
<<<<<<< HEAD
    for (k = 0; k < strlen(charProgEndValue); k++)
    {
      myChar =  pgm_read_byte_near(charProgEndValue + k);
      myfile.print(myChar);
    }
    /////////////////////////////////////////////////////////////
    /*for (k = 0; k < strlen(charProgId); k++)
=======
    
     for (k = 0; k < strlen(charProgFinCap); k++)
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    {
      myChar =  pgm_read_byte_near(charProgFinCap + k);
      myfile.print(myChar);
    }
    
     for (k = 0; k < strlen(charProg9); k++)
    {
      myChar =  pgm_read_byte_near(charProg9 + k);
      myfile.print(myChar);
    }
    myfile.print(sDate);
     for (k = 0; k < strlen(charProgValueType); k++)
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    myfile.print(vitesseMoteur);
     for (k = 0; k < strlen(charProgId2); k++)
    {
      myChar =  pgm_read_byte_near(charProgId2 + k);
      myfile.print(myChar);
<<<<<<< HEAD
    }*/
    
    ///////////////////////////////////////////////////////////////
    for (k = 0; k < strlen(charProgId); k++)
=======
    }
    myfile.print(sDate);
     for (k = 0; k < strlen(charProgValueType); k++)
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    {
      myChar =  pgm_read_byte_near(charProgValueType + k);
      myfile.print(myChar);
    }
    if(alarmeVib)
    {
      myfile.println("true");
      alarmeVib = false;
    }
    else
      myfile.println("false");
      
      
       for (k = 0; k < strlen(charProgFinCap); k++)
    {
      myChar =  pgm_read_byte_near(charProgFinCap + k);
      myfile.print(myChar);
    }
    
     for (k = 0; k < strlen(charProgFinCap); k++)
    {
      myChar =  pgm_read_byte_near(charProgFinCap + k);
      myfile.print(myChar);
    }
  // ferme le fichier Json
  if(finFichier)
  {
<<<<<<< HEAD
    finFichier = false;
    //finFichier = true;
    for (k = 0; k < strlen(fin); k++)
=======
    finFichier = true;
     for (k = 0; k < strlen(fin); k++)
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
    {
      myChar =  pgm_read_byte_near(fin + k);
      myfile.print(myChar);
    }
<<<<<<< HEAD
    myfile.close();
  // EnvoieDonne();
=======
  }
  
  myfile.println("\n\r");
  //freeMem("RAM restante: ");
  myfile.close();
  
  Serial.println("done.");

  pinMode(10, INPUT);
}
boolean isMotorOn(void)
{
  ampBatterie = capteurs.getCurrent();
  if(ampBatterie >= 0)
  {
    return true;
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
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
<<<<<<< HEAD
  if(tensionBatterie >= 0)
  {
    return true;
=======
  // envoie des donnes a 1h am
  if(date.temp.heure = 1 && date.temp.seconde >= 59)
  {
    return false;
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
  }
  else
  {
    return true;
  }
}

<<<<<<< HEAD
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

=======
>>>>>>> parent of 7ece9a0... changement pour la sd fonctionnel++
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

