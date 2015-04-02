// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
#iclude <avr>
#include <ArduinoJson.h>
#include <stdio.h>
#include<string.h>
#include <SD.h>

File myFile;
const int chipSelect = 4;
void setup() {
  Serial.begin(9600);
  //variable de test pour la simulation des températures
  float tempAmbi = 0.0;
  float tempMot1 = 0.0;
  float tempMot2 = 0.0;
  float frqVibration =0.0; 
  float mesure24volts = 0.0;
  float mesureCourant_Amp = 0.0;
//variables pour pour la création du fichier Json
     // ID capteur de température
    char *IdCapteurMot1 = "001";
    char *IdCapteurMot2 = "002";
    char *IdFrequence = "003";
    char *IdMesureU_24v = "004";
    char *IdMesureI_amp = "005";
    char *IdTempAmbi = "006";
    
    char *StationSenegal = "StationSenegal";
    char *dateTime = "DateTime";
    char *stationid = "stationid";
    char *IdStation = "Sen002";
    char *vDateTime = "12:30:26:20:03:2015";
    char *modeLecture = "regularreading";
    char *sensorUnIdCapteur = "su0001";  // sensorUnitId catpteur tempMoteur     
    
    char *test = "test.jso";
   //while(1)
   //{
      tempAmbi = random(40);
      tempMot1 = random(100);
      tempMot2 = random(100);
      frqVibration =random(200);
      mesure24volts = random(6);
      mesureCourant_Amp = random(600);
      
      
  
      StaticJsonBuffer<300> jsonBuffer;
      JsonObject& root = jsonBuffer.createObject();
      root[StationSenegal] ;
      root[dateTime] = vDateTime;
      root[modeLecture];
      root["sensorunitid"] = sensorUnIdCapteur;
      root["event"];
        
      JsonArray& data = root.createNestedArray("data");
      data.add("temp Moteur 1 en degresC");
      data.add(IdCapteurMot1);// = IdCapteurMot1
      data.add("value");  // titre
      data.add(tempMot1, 1);  // valeur en float
      
      data.add("temp Moteur 2 en degresC:");
      data.add(IdCapteurMot2);
      data.add("value");
      data.add(tempMot2, 1);
     
      data.add("vibration en Hz:");
      data.add(IdFrequence);
      data.add("value");
      data.add(frqVibration,1);
      
      data.add("Mesure en tension :");
      data.add(IdMesureU_24v);
      data.add("value");
      data.add(mesure24volts,1);
      
      data.add("Mesure intensite en amperes :");
      data.add(IdMesureI_amp);
      data.add("value");
      data.add(mesureCourant_Amp,1);
      
      data.add("Temperature ambiante en degresC:");
      data.add(IdTempAmbi);
      data.add("value");
      data.add(tempAmbi,1);
     
      root.prettyPrintTo(Serial);
      if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      return;
      }
      Serial.println("initialization done.");
    
      myFile = SD.open(test, FILE_WRITE);
      if(myFile)
      {
        Serial.println("done1");
        myFile.println("\n\r\n\r");
        root.prettyPrintTo(myFile);
        Serial.println("done2");
        myFile.close();
        Serial.println("done3");
      }
      else
      {
        Serial.println("erreur");
      }
      
   //};
}

void loop() {
  
  
   
}
