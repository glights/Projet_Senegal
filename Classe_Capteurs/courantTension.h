// file: courantTension.h
/*
*	auteur: Guillaume & Ilalio
*	verison: 1
*
*/


//fonction pour prendre une mesure de courant � la batterie
float getCourantBatterie(void);

//fonction pour prendre une mesure de tension � la batterie
float getTensionBatterie(void);


uint16_t adc_read(uint8_t adcx);