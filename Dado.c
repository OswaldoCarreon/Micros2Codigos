/*
 * Practica04-Dado.c
 *
 * Created: 09/02/2021 05:25:42 p. m.
 * Author : Oswald
 */ 


#define  F_CPU 1000000UL
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
#include <avr/interrupt.h>	 //Para poder manejar interrupciones
#include <time.h>


//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER "LUGAR"
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
//*************************************************************************

volatile uint8_t dado = 1;
int main(void)
{
	
    GIFR = 0x00;
	MCUCR = 0b00000011; //Flanco de subida para int0
	GICR =  0b01000000; //Habilitar interrupciones
	
	DDRD = 0x00; //entrada
	PORTD = 0xFF; //pull up
	
	DDRA = 0xFF;
	PORTA = 0x00;
	
	sei();
	srand (time(NULL));
    while (1) {}
}



ISR(INT0_vect){
	_delay_us(60);
	while(cero_en_bit(&PIND,2)) {}
	_delay_us(60);
	
	dado = rand()%6 + 1;
	
	
	switch(dado) {
		case 1: PORTA = 0b00001000;
		break;
		case 2: PORTA = 0b00100010;
		break;
		case 3: PORTA = 0b01001001;
		break;
		case 4: PORTA = 0b01100011;
		break;
		case 5: PORTA = 0b01101011;
		break;
		default: PORTA = 0b01110111
	}
	
}


uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (*LUGAR&(1<<BIT));
}