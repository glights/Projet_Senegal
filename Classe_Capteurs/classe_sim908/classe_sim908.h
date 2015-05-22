#include <Arduino.h>

class classe_sim908
{
	public:
	
	char _gpsDate[14];

	int anne = 0;
	char mois = 0;
	char jour = 0;
	char heure = 0;
	char minute = 0;
	char seconde = 0;
	
	/*void getAnneGPS(void);
	
	void getMoisGPS(void);
	
	void getJourGPS(void);
	
	void getHeureGPS(void);
	
	void getMinuteGPS(void);
	
	void getSecondeGPS(void);*/
	
	void power_onSim(void);
	
	void power_offSim(void);
	
	void getGpsString(void);
	
	void sendJson(void);
	
	void envoieJson(long fileSize);
	
	void setSim908(void);
	
	private:
	
	uint8_t sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout);
	
};