#include<stdlib.h>
#include <SD.h> 
#include <SPI.h>
#include <TimerOne.h>
#include <classe_date.h>
#include <class_capteurs.h>

File myfile;
class_capteurs capteurs;
Classe_date date;

const char debut[] = "{\"stationmessage\":{\"datetime\":\"";
const char apDebut[] = "{\",\"stationid\":\"sen002\",\"\":\"regularreading\",\"event\":[";
const char dateLive[] = "{\"sensorunitid\":\"su0001\",\"data\":[{\"datetime\":\"";
const char charBattery1[] = "\",\"id\":\"001\",\"valuetype\":\"max\",\"value\":";
const char charBattery2[] = "},{\"id\":\"002\",\"valuetype\":\"max\",\"value\":";
const char charTemp1[] = "}]},{\"sensorunitid\":\"su0002\",\"data\":[{\"id\":\"001\",\"valuetype\":\"max\",\"value\":";
const char charTemp2[] = "},{\"id\":\"002\",\"valuetype\":\"max\",\"value\":";
const char charTemp3[] = "},{\"id\":\"003\",\"valuetype\":\"max\",\"value\":";
const char charAcc1[] = "}]},{\"sensorunitid\":\"su0003\",\"data\":[{\"id\":\"001\",\"valuetype\":\"max\",\"value\":";
const char charAcc2[] = "},{\"id\":\"002\",\"valuetype\":\"max\",\"value\":";
const char avFin[] = "}]}";
const char fin[] = "]}}";

char *txt = ".txt";
String sDate = "19:10:25:15:04:2015";
float tensionBatterie = 55.45;
float ampBatterie = 60.3;
float tempAmbiante = 36.65;
float tempMoteur1 = 100.35;
float tempMoteur2 = 100.98;
double vitesseMoteur = 6000;
boolean alarmeVib = false;

int vitesseHz = 0;

int count = 0;

boolean nouveauFichier = true;
boolean finFichier = true;


void setup (void)
{
  Serial.begin(9600);
  Timer1.initialize(1000000);
  capteurs.begin();
  Timer1.attachInterrupt(timer1_isr);
  attachInterrupt(0, vitesse, FALLING);
  attachInterrupt(1, intAlarme, FALLING);
  date.setDate(2015,4,2);
  date.setHeure(16,24,33);
  delay(5000);
}

void loop(void)
{
  if(count >= 5)
  {
    count = 0;
    //if(isMotorOn)
    //{
        sDate = date.getDateComplete();
        Serial.print("date: ");
        Serial.println(sDate);
        Serial.print("courant: ");
        Serial.println(ampBatterie);
        tensionBatterie = capteurs.getVoltage();
        Serial.print("tension: ");
        Serial.println(tensionBatterie);
        tempAmbiante = capteurs.getTempAmbi();
        Serial.print("temperature Ambiante: ");
        Serial.println(tempAmbiante);
        tempMoteur1 = capteurs.getTempMoteur1();
        Serial.print("temperature Moteur1: ");
        Serial.println(tempMoteur1);
        tempMoteur2 = capteurs.getTempMoteur2();
        Serial.print("temperature Moteur2: ");
        Serial.println(tempMoteur2);
        Serial.print("vitesse du moteur");
        Serial.println(vitesseMoteur);
        Serial.print("etat Alarme moteur:");
        
        if(alarmeVib)
        {
          Serial.println("true");
          alarmeVib = false;
        }
        else
          Serial.println("false");
          
        ecritureSD();
    //}
  }
}

void ecritureSD(void)
{
  pinMode(10, OUTPUT);
  
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
  }
  Serial.println("initialization done.");
  
  myfile = SD.open(date.getDateFichier(), FILE_WRITE);

  // ouvre le fichier Json
  if(nouveauFichier)
  {
    //nouveauFichier = false;
    myfile.print(debut);
    myfile.print(sDate);
    myfile.print(apDebut);
  }
  myfile.print(dateLive);
  myfile.print(sDate);
  myfile.print(charBattery1);
  myfile.print(tensionBatterie);
  myfile.print(charBattery2);
  myfile.print(ampBatterie);
  myfile.print(charTemp1);
  myfile.print(tempAmbiante);
  myfile.print(charTemp2);
  myfile.print(tempMoteur1);
  myfile.print(charTemp3);
  myfile.print(tempMoteur2);
  myfile.print(charAcc1);
  myfile.print(vitesseMoteur);
  myfile.print(charAcc2);
  myfile.print(alarmeVib);
  myfile.print(avFin);
  
  // ferme le fichier Json
  if(finFichier)
  {
    //finFichier = false
    myfile.print(fin);
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
  if(ampBatterie > 10)
  {
    return true;
  }
  else
  {
    return false;
  }
}

boolean heureEnvoieDonne(void)
{
  // envoie des donnes a 1h am
  if(date.temp.heure = 1 && date.temp.seconde >= 59)
  {
    return false;
  }
  else
  {
    return true;
  }
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
  vitesseMoteur = vitesseHz*60;
  vitesseHz = 0;
  count++;
  date.incremanteTemp();
}

struct __freelist {
  size_t sz;
  struct __freelist *nx;
};

extern char * const __brkval;
extern struct __freelist *__flp;

uint16_t freeMem(uint16_t *biggest)
{
  char *brkval;
  char *cp;
  unsigned freeSpace;
  struct __freelist *fp1, *fp2;

  brkval = __brkval;
  if (brkval == 0) {
    brkval = __malloc_heap_start;
  }
  cp = __malloc_heap_end;
  if (cp == 0) {
    cp = ((char *)AVR_STACK_POINTER_REG) - __malloc_margin;
  }
  if (cp <= brkval) return 0;

  freeSpace = cp - brkval;

  for (*biggest = 0, fp1 = __flp, fp2 = 0;
     fp1;
     fp2 = fp1, fp1 = fp1->nx) {
      if (fp1->sz > *biggest) *biggest = fp1->sz;
    freeSpace += fp1->sz;
  }

  return freeSpace;
}

uint16_t biggest;

void freeMem(char* message) {
  Serial.print(message);
  Serial.print(":\t");
  Serial.println(freeMem(&biggest));
}

void Sim900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  delay(5000);
}

