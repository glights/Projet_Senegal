// .cpp
	#include "classe_sim908.h"
	/*
	char *classe_sim908::getAltitude(void)
	{
		char altitudeGPS[10];
		int i;
		for(i=0;i<10;i++)
		{
			altitudeGPS[i] = _gpsString[28+i];
		}
		return altitudeGPS;
		
	}
	
	char *classe_sim908::getLongitude(void)
	{
		char longitudeGPS[12];
		int i;
		for(i=0;i<12;i++)
		{
			longitudeGPS[i] = _gpsString[3+i];
		}
		return longitudeGPS;
		
	}
	
	char *classe_sim908::getLatitude(void)
	{
		char latitudeGPS[11];
		int i;
		for(i=0;i<11;i++)
		{
			latitudeGPS[i] = _gpsString[16+i];
		}
		return latitudeGPS;
	}
	
	int classe_sim908::getAnneGPS(void)
	{
		char AnneGPS[4];
		int i;
		for(i=0;i<4;i++)
		{
			AnneGPS[i] = _gpsString[43+i];
		}
		
		return AnneGPS.toInt();
		
	}
	
	int classe_sim908::getMoisGPS(void)
	{
		char moisGPS[2];
		int i;
		for(i=0;i<2;i++)
		{
			moisGPS[i] = _gpsString[45+i];
		}
		return moisGPS.toInt();
		
	}
	
	int classe_sim908::getJourGPS(void)
	{
		char jourGPS[2];
		int i;
		for(i=0;i<2;i++)
		{
			jourGPS[i] = _gpsString[47+i];
		}
		return jourGPS.toInt();
		
	}
	
	int classe_sim908::getHeureGPS(void)
	{
		char heureGPS[2];
		int i;
		for(i=0;i<2;i++)
		{
			heureGPS[i] = _gpsString[49+i];
		}
		return heureGPS.toInt();
		
	}
	
	int classe_sim908::getMinuteGPS(void)
	{
		char minuteGPS[2];
		int i;
		for(i=0;i<2;i++)
		{
			minuteGPS[i] = _gpsString[51+i];
		}
		return minuteGPS.toInt();
		
	}
	
	int classe_sim908::getSecondeGPS(void)
	{
		char secondeGPS[2];
		int i;
		for(i=0;i<2;i++)
		{
			secondeGPS[i] = _gpsString[53+i];
		}
		return secondeGPS.toInt();
		
	}*/
	
	void classe_sim908::power_onSim(void)
	{
		uint8_t answer=0;
    
		// checks if the module is started
		answer = sendATcommand("AT", "OK", 2000);
		if (answer == 0)
		{
			// power on pulse
			digitalWrite(6,HIGH);
			delay(3000);
			digitalWrite(6,LOW);
		
			// waits for an answer from the module
			while(answer == 0){    
				// Send AT every two seconds and wait for the answer
				answer = sendATcommand("AT", "OK", 2000);    
			}
		}
		delay(10000);
	}
	
	void classe_sim908::power_offSim(void)
	{
		uint8_t answer=0;
    
		// checks if the module is started
		answer = sendATcommand("AT", "OK", 2000);
		if (answer == 1)
		{
			// power on pulse
			digitalWrite(6,HIGH);
			delay(3000);
			digitalWrite(6,LOW);
		
			// waits for an answer from the module
			while(answer == 0){    
				// Send AT every two seconds and wait for the answer
				answer = sendATcommand("AT", "OK", 2000);    
			}
		}
	}
	
	void classe_sim908::setSim908(void)
	{
		sendATcommand("AT+SAPBR=3,1,\"APN\",\"ltemobile.apn\"","OK", 2000);
		sendATcommand("AT+SAPBR=1,1","OK", 10000);	
	}
	
	void classe_sim908::envoieJson(long fileSize)
	{
		String strFileSize = String(fileSize, DEC);
		int k;
		char myChar;
		
		
		sendATcommand("AT+HTTPINIT","OK",2000);
		sendATcommand("AT+HTTPPARA=\"CID\",1","OK",2000);
		sendATcommand("AT+HTTPPARA=\"URL\",\"cloudiaproject.org/data.php\"","OK",2000);
		sendATcommand("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"","OK",2000);
		Serial.print("AT+HTTPDATA=");
		Serial.print(strFileSize);
		sendATcommand(",20000","DOWNLOAD",2000);
	}
	
	void classe_sim908::sendJson(void)
	{
		int k;
		char myChar;
		
		sendATcommand("AT+HTTPACTION=1","OK",2000);
		delay(8000);
		sendATcommand("AT+HTTPREAD","Successfully parsed JSON",2000);
		sendATcommand("AT+HTTPTERM","OK",2000);
		
	}
	
	uint8_t classe_sim908::sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout)
	{
		uint8_t x=0,  answer=0;
		char response[97];
		unsigned long previous;

		memset(response, '\0', 97);    // Initialize the string
		
		delay(100);
		
		// Clean the input buffer
		while( Serial.available() > 0) Serial.read();    
		
		Serial.println(ATcommand);    // Send the AT command 


		x = 0;
		previous = millis();

		// this loop waits for the answer
		do{

			if(Serial.available() != 0){    
				response[x] = Serial.read();
				x++;
				// check if the desired answer is in the response of the module
				if (strstr(response, expected_answer1) != NULL)    
				{
					answer = 1;
				}
			}
			// Waits for the asnwer with time out
		}while((answer == 0) && ((millis() - previous) < timeout));    

		return answer;
	}
	void classe_sim908::getGpsString(void)
	{
		int counter;
		long previous;
		uint8_t answer = 0;
		
		sendATcommand("AT+CGPSPWR=1","OK", 2000);
		sendATcommand("AT+CGPSRST=0","OK", 2000);
		  
		// waits for fix GPS
		while( (sendATcommand("AT+CGPSSTATUS?", "2D Fix", 5000) || 
			sendATcommand("AT+CGPSSTATUS?", "3D Fix", 5000)) == 0 );
		
		while( Serial.available() > 0) Serial.read();
		delay(100);
		//request info
		sendATcommand("AT+CGPSINF=0", "AT+CGPSINF=0\r\n\r\n", 2000);
		  
		counter = 0;
		answer = 0;
		memset(_gpsString, '\0', 97);    // Initialize the string
		previous = millis();
		// this loop waits for the NMEA string
		do{
		
			if(Serial.available() != 0){    
				_gpsString[counter] = Serial.read();
				counter++;
				// check if the desired answer is in the response of the module
				if (strstr(_gpsString, "OK") != NULL)    
				{
					answer = 1;
				}
			}
		// Waits for the asnwer with time out
		}while((answer == 0) && ((millis() - previous) < 2000));  
			
		_gpsString[counter] = '\0';
	}