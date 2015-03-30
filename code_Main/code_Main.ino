
#define PERIODE_TIMER1 1000000 // en micro secondes

#include <SD.h>

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
String sDate;
float temperatureMoteur1 = 0.0;
float temperatureMoteur2 = 0.0;
float temperatureAmbiante = 0.0;
float mesureCourant = 0.0;
float mesureTension = 0.0;
boolean alarmeVibration = false;
long vitesseRPM = 0;
int vitesse = 0;
int vitesseHz = 0;
int count = 0;
int anVib = 0;
int vib = 0;

char *IdCapteurMot1 = "001";
char *IdCapteurMot2 = "002";
char *IdFrequence = "003";
char *IdMesureU_24v = "004";
char *IdMesureI_amp = "005";
char *IdTempAmbi = "006";
char *IdVitesseRPM = "007";

char *StationSenegal = "StationSenegal";
char *dateTime = "DateTime";
char *stationid = "stationid";
char *IdStation = "Sen002";
String vDateTime = setDateTime_js("10:51:23:27/03/2015");
char *modeLecture = "regularreading";
char *sensorUnIdCapteur = "su0001";  // sensorUnitId catpteur tempMoteur

void setup(void)
{
  Serial.begin(9600);
  initialisation();
}

void loop(void)
{
  temperatureAmbiante = capteurs.getTempAmbi();
  temperatureMoteur1 = capteurs.getTempMoteur1();
  temperatureMoteur2 = capteurs.getTempMoteur2();
  mesureCourant = capteurs.getCurrent();
  mesureTension = capteurs.getVoltage();
  
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root[StationSenegal] ;
  root[dateTime] = vDateTime;
  root[modeLecture];
  root["sensorunitid"] = sensorUnIdCapteur;
  root["event"];

  JsonArray& data = root.createNestedArray("data");
  data.add("temp moteur1 en degresC");
  data.add(IdCapteurMot1);// = IdCapteurMot1
  data.add("value");  // titre
  data.add(temperatureMoteur1, 1);  // valeur en float

  data.add("temp Moteur 2 en degresC:");
  data.add(IdCapteurMot2);
  data.add("value");
  data.add(temperatureMoteur2, 1);

  data.add("AlarmeVibration :");
  data.add(IdFrequence);
  data.add("value");
  data.add(alarmeVibration, 1);

  data.add("Mesure en tension :");
  data.add(IdMesureU_24v);
  data.add("value");
  data.add(mesureTension, 1);

  data.add("Mesure intensite en amperes :");
  data.add(IdMesureI_amp);
  data.add("value");
  data.add(mesureCourant, 1);

  data.add("Temperature ambiante en degresC:");
  data.add(IdTempAmbi);
  data.add("value");
  data.add(temperatureAmbiante, 1);
  
  //setVitesseRPM_js
  data.add("Vitesse RPM:");
  data.add(IdVitesseRPM);
  data.add("value");
  data.add(vitesseHz*60);
  
  root.prettyPrintTo(Serial);
  pinMode(10, OUTPUT);
 
  sprintf(date,"%s.txt",temp.getDate());
  myFile = SD.open(date, FILE_WRITE);
  
  if(myfile)
  {
    
  }
  
  if(count >= 4)
  {
    count = 0;
    alarmeVibration = true;
  }
  
}

void initialisation(void)
{
  Serial.print("Initialisation des capteurs....");
  Timer1.initialize(PERIODE_TIMER1); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
   
   pinMode(10, OUTPUT);
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  Serial.println("initialization done.");
  
  pinMode(2,INPUT);
  attachInterrupt(2,interruptVitesse,FALLING);
  
  pinMode(3,INPUT);
  attachInterrupt(3,interruptVibAlarm,FALLING);
  
  if(capteurs.begin())
  {
    Serial.println("erreur dinitialisation des capteurs");
    return;
  }
    
  temp.setHeure(3,24,27);
  temp.setDate(2015,3,27);
  delay(1000);
  Serial.println("Initialisation termine");
  delay(300);
  Serial.println("commencement de prise de donnees des capteurs");
  
}

void timerIsr()
{
  temp.incremanteTemp();
  vitesseHz = vitesse;
  vitesse = 0;
  
  if(anVib == vib)
    vib = 0;
  else
  {
    count++;
  }
  anVib = vib;
}

void interruptVitesse()
{
  vitesse++;
}

void interruptVibAlarm()
{
  vib++;
}
