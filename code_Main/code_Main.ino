#include <SD.h> 
#include <SPI.h>
#include <TimerOne.h>
#include <classe_date.h>
#include <class_capteurs.h>

File myfile;
class_capteurs capteurs;
Classe_date date;

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
boolean alarmeVib = false;

int vitesseHz = 0;

int count = 0;

boolean nouveauFichier = true;
boolean finFichier = false;

void setup (void)
{
  Serial.begin(9600);
  Timer1.initialize(1000000);
  Serial.println("\n\rstarting...");
  capteurs.begin();
  Timer1.attachInterrupt(timer1_isr);
  attachInterrupt(0, vitesse, FALLING);
  attachInterrupt(1, intAlarme, FALLING);
  //date.setDate(2015,4,2);
  //date.setHeure(16,24,33);
  delay(5000);
}

void loop(void)
{
  int k;
  char myChar;
  
  if(count >= 5)
  {
    count = 0;
    if(isMotorOn)
    {
        //sDate = date.getDateComplete();
        Serial.println();
        Serial.print("date: ");
        Serial.println(sDate);
        ampBatterie = capteurs.getCurrent();
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
    }
  }
}

void ecritureSD(void)
{
  char myChar;
  int k;
  
  pinMode(10, OUTPUT);
  
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
  }
  Serial.println("initialization done.");
  
  myfile = SD.open(date.getDateFichier(), FILE_WRITE);

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
    
    for (k = 0; k < strlen(charProg1); k++)
    {
      myChar =  pgm_read_byte_near(charProg1 + k);
      myfile.print(myChar);
    }
  }
  
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
    
    for (k = 0; k < strlen(charProg6); k++)
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
    
    
     for (k = 0; k < strlen(charProgFinCap); k++)
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
    }
    myfile.print(sDate);
     for (k = 0; k < strlen(charProgValueType); k++)
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
    finFichier = true;
     for (k = 0; k < strlen(fin); k++)
    {
      myChar =  pgm_read_byte_near(fin + k);
      myfile.print(myChar);
    }
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

