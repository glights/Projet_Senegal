// .cpp
#include "classe_sim908.h"
/*
void classe_sim908::getAnneGPS(void)
{
	int i;
	for(0;i<4;i++)
	{
		_gpsDate[i] -= '0';
	}
	anne = (1000*_gpsDate[0])+(100*_gpsDate[1])+(10*_gpsDate[2])+_gpsDate[3];
}

void classe_sim908::getMoisGPS(void)
{
	char moisGPS[2];
	int i;
	for(i=0;i<2;i++)
	{
		moisGPS[i] -= '0';
	}
	mois = (10*moisGPS[0])+(moisGPS[1]);
	
}

void classe_sim908::getJourGPS(void)
{
	char jourGPS[2];
	int i;
	for(i=0;i<2;i++)
	{
		jourGPS[i] -= '0';
	}
	jour = (10*jourGPS[0])+(jourGPS[1]);
	
}

void classe_sim908::getHeureGPS(void)
{
	char heureGPS[2];
	int i;
	for(i=0;i<2;i++)
	{
		heureGPS[i] -= '0';
	}
	heure = (10*heureGPS[0])+(heureGPS[1]);
	
}

void classe_sim908::getMinuteGPS(void)
{
	char minuteGPS[2];
	int i;
	for(i=0;i<2;i++)
	{
		minuteGPS[i] -= '0';
	}
	minute = (10*minuteGPS[0])+(minuteGPS[1]);
	
}

void classe_sim908::getSecondeGPS(void)
{
	char secondeGPS[2];
	int i;
	for(i=0;i<2;i++)
	{
		secondeGPS[i] -= '0';
	}
	seconde = (10*secondeGPS[0])+(secondeGPS[1]);
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
	//sendATcommand("AT+SAPBR=3,1,\"USER\",\"orange\"","OK", 2000);
	//sendATcommand("AT+SAPBR=3,1,\"PWD\",\"orange\"","OK", 2000);
	sendATcommand("AT+SAPBR=1,1","OK", 10000);
}

void classe_sim908::envoieJson(long fileSize)
{
	//String strFileSize = String(fileSize, DEC);
	//char strFileHttp[40];
	long k = fileSize;
	//Serial.print(fileSize);
	//sprintf(strFileHttp, "AT+HTTPDATA=%l", fileSize);
	sendATcommand("AT+HTTPINIT","OK",2000);
	Serial.print("AT+HTTPDATA=");
	Serial.print(k);
	sendATcommand(",20000","DOWNLOAD",2000);
	/*sendATcommand("AT+HTTPPARA=\"CID\",1","OK",2000);
	sendATcommand("AT+HTTPPARA=\"URL\",\"cloudiaproject.org/data.php\"","OK",2000);
	sendATcommand("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"","OK",2000);*/
}

void classe_sim908::sendJson(void)
{
	int k;
	char myChar;
	
	sendATcommand("AT+HTTPPARA=\"CID\",1","OK",2000);
	sendATcommand("AT+HTTPPARA=\"URL\",\"cloudiaproject.org/data.php\"","OK",2000);
	sendATcommand("AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded\"","OK",2000);
	sendATcommand("AT+HTTPACTION=1","OK",2000);
	delay(5000);
	sendATcommand("AT+HTTPREAD","Successfully parsed JSON",2000);
	sendATcommand("AT+HTTPTERM","OK",2000);
	
}

uint8_t classe_sim908::sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout)
{
	uint8_t x=0,  answer=0;
	char response[40];
	unsigned long previous;

	memset(response, '\0', 40);    // Initialize the string
	
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
	char virgule = 0;
	
	sendATcommand("AT+CGPSPWR=1","OK", 2000);
	sendATcommand("AT+CGPSRST=0","OK", 2000);
	  
	// waits for fix GPS
	/*while( (sendATcommand("AT+CGPSSTATUS?", "2D Fix", 5000) ||
		sendATcommand("AT+CGPSSTATUS?", "3D Fix", 5000)) == 0 );*/
	
	memset(_gpsDate, '\0', 14);
	delay(100);
	//clean buffer
	while( Serial.available() > 0) Serial.read();
	//request info
	sendATcommand("AT+CGPSINF=0", "AT+CGPSINF=0\r\n\r\n", 2000);
	  
	counter = 0;
	previous = millis();

	while((virgule!=4))
	{
		if(Serial.available() != 0)
		{
			_gpsDate[0] = Serial.read();
			if(_gpsDate[0] == ',')
			{
				virgule++;
			}
		}
	}
	
	do
	{
		if(Serial.available() != 0)
		{
			_gpsDate[counter] = Serial.read();
			_gpsDate[counter] -= '0'; 
			counter++;
		}
	}while((_gpsDate[counter] != '.') && ((millis() - previous) < 2000));
	Serial.println(_gpsDate);
}