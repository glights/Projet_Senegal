// Copyright Benoit Blanchon 2014
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <ArduinoJson.h>
#include <stdio.h>
#include<string.h>
#include <SD.h>

const int chipSelect = 4;

void setup() {
  Serial.begin(9600);
  
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  float tempAmbi = 0.0;
  float tempMot1 = 0.0;
  float tempMot2 = 0.0;
  float frqVibration =0.0; 
  float mesure24volts = 0.0;
  float mesureCourant_mA = 0.0;
 
  //String fichierJson[255] = "\0";

 while(1)
 {
    tempAmbi = random(40);
    tempMot1 = random(100);
    tempMot2 = random(100);
    frqVibration =random(200);
    mesure24volts = random(6);
    mesureCourant_mA = random(600);
    
    delay(1000);
   
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["projet"] = "moulin soleil";
    root["ID"] = "Sen002";
  
  // construction du tableau de donnée Json
    JsonArray& data = root.createNestedArray("data");
    data.add("temperature Ambiante");
    
    data.add(tempAmbi, 2);  // 2 is the number of decimals to print;
    
    data.add("temperature moteur1");
    data.add(tempMot1, 2);  // 2 is the number of decimals to print;
    
    data.add("temperature moteur2");
    data.add(tempMot2, 2);
    
    data.add("vibration moteur");
    data.add(frqVibration, 2);
    
    data.add("Mesure 24V");
    data.add(mesure24volts, 2);
    
    data.add("Mesure en mA");
    data.add(mesureCourant_mA, 2);
    
    
    

    Serial.println();
    root.prettyPrintTo(Serial);
    
   // sprintf();
  };
        /*
          // This prints:
        {
        
          "sensor": "moulin soleil",
        
          "data": [
            "temperature Ambiante"
            1.00,  // valeur random() pour test 
            
            "temperature moteur1"
            53.00, 
            
            "temperature moteur2"
            77.00,
         
            "vibration moteur"
            8.00
        
          ]
        
        }*/
}

void loop() {
  
  String dataString = "";
  
   // read three sensors and append to the string:
  for (int value = 0; value < 3; value++) {
      
   //manque du code ici
   //fomatage du buffer
    if (value < 2) {
      dataString += ","; 
    }
  }
  
   // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
 
}
