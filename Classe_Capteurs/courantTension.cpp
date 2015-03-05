// file: courantTension.cpp
/*
*	auteur: Guillaume & Ilalio
*	verison: 1
*	
*/

//includes
#include <avr/io.h>
#include <stdint.h>

#define ADC_PIN			0

#define	LED_PIN			PB0

#define ADC_THRESHOLD	512

//fonction pour prendre une mesure de courant à la batterie
float getCourantBatterie(void)
{

	ADCSRA |= _BV(ADEN);

	DDRB |= _BV(LED_PIN);


	if (adc_read(ADC_PIN) > ADC_THRESHOLD)
		PORTB |= _BV(LED_PIN);
	else
		PORTB &= ~_BV(LED_PIN);
}

//fonction pour prendre une mesure de tension à la batterie
float getTensionBatterie(void)
{
	
}

uint16_t adc_read(uint8_t adcx) {
	
	ADMUX &= 0xf0;
	ADMUX |= adcx;


	ADCSRA |= _BV(ADSC);

	while ((ADCSRA & _BV(ADSC)));

	return ADC;
}