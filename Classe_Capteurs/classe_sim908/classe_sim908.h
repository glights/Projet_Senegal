#include <Arduino.h>

class classe_sim908
{
	public:
	/*const PROGMEM char progHttpInit[12] = "AT+HTTPINI";
	const PROGMEM char progHttpParaCid[22] = "AT+HTTPPARA=\"CID\",";
	const PROGMEM char progHttpParaUrl[51] = "AT+HTTPPARA=\"URL\",\"cloudiaproject.org/data.php";
	const PROGMEM char progHttpParaCon[61] = "AT+HTTPPARA=\"CONTENT\",\"application/x-www-form-urlencoded";
	const PROGMEM char progHttpData1[14] = "AT+HTTPDATA=";
	const PROGMEM char progHttpData2[7] = ",1000";
	const PROGMEM char progHttpAction[16] = "AT+HTTPACTION=";
	const PROGMEM char progHttpRead[12] = "AT+HTTPREA";
	const PROGMEM char progHttpTerm[12] = "AT+HTTPTER";*/
	
	char _gpsString[97];
	
	char *getAltitude(void);
	
	char *getLongitude(void);
	
	char *getLatitude(void);
	
	int getAnneGPS(void);
	
	int getMoisGPS(void);
	
	int getJourGPS(void);
	
	int getHeureGPS(void);
	
	int getMinuteGPS(void);
	
	int getSecondeGPS(void);
	
	void power_onSim(void);
	
	void power_offSim(void);
	
	void getGpsString(void);
	
	void sendJson(void);
	
	void envoieJson(long fileSize);
	
	void setSim908(void);
	
	private:
	
	uint8_t sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout);
	
};