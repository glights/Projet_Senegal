#include <SD.h> 
#include <SPI.h>
#include <TimerOne.h>
#include <classe_date.h>
#include <class_capteurs.h>

File myfile;
class_capteurs capteurs;
Classe_date date;

const PROGMEM char debut[] = "{\"stationmessage\":{\"datetime\":\"";
const PROGMEM char debut2[] = "\",\"stationid\":\"sen002\",\"eventtype\":\"regularreading\",\"event\":[{\"sensorunit\": \"su0009\",\"data\": [";
const PROGMEM char charProgId[] = "{\"id\":\"0";
const PROGMEM char charProgDateTime[] = "\",\"datetime\":\"";
const PROGMEM char charProgValueType[] = "\",\"valuetype\":\"asis\",\"value\":\"";
const PROGMEM char charProgEndValue[] = "\"},";
const PROGMEM char fin[] = "\"}]}]}}";

String sDate = "2015-04-17 09:23:27";
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
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  Timer1.initialize(1000000);
  Serial.println("\n\rstarting...");
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
  int k;
  char myChar;
  
  if(count >= 5)
  {
    count = 0;
    //if(isMotorOn)
    //{
        sDate = date.getDateComplete();
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
        
        /*if(heureEnvoieDonne())
            envoieDonne();*/
            
        if(alarmeVib)
        {
          Serial.println("true");
        }
        else
          Serial.println("false");
        
        ecritureSD();
        nouveauFichier = false;
        alarmeVib = false;
       
    //}
  }
 /* if(count >= 5)
        {
         ecritureSD();
          finFichier = false;
        }*/
}


void ecritureSD(void)
{
  char myChar;
  int k;
  
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
  }
  Serial.println("initialization done.");
  
  myfile = SD.open("allo1.txt", FILE_WRITE);

  // ouvre le fichier Json
  //if(nouveauFichier)
  //{
    //nouveauFichier = false;
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
 //}
  
  
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
    myfile.print(tempAmbiante);
    
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
    for (k = 0; k < strlen(charProgId); k++)
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
    }
    
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
  //if(finFichier)
  //{
    //finFichier = true;
    for (k = 0; k < strlen(fin); k++)
    {
      myChar =  pgm_read_byte_near(fin + k);
      myfile.print(myChar);
    }
    
  //}
  
  
  
  myfile.println("\n\r");
  //freeMem("RAM restante: ");
  myfile.close();
  
  Serial.println("done.");

  //pinMode(10, INPUT);
}
boolean isMotorOn(void)
{
  
  if(tensionBatterie >= 5)
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
  if(date.temp.heure == 23 && date.temp.minute >= 59 && date.temp.seconde >= 59)
  {
    return true;
    finFichier = true;
  }
  else
  {
    return false;
  }
}

void envoieDonne(void)
{
  Serial.println("envoie des donnees...");
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

