/*
 * Practica010-A-OSWALDO-MAX.c
 *
 * Created: 01/02/2021 12:36:12 p. m.
 * Author : Oswal
 */ 


#define  F_CPU 1000000UL
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
//#include <avr/interrupt.h>	 //Para poder manejar interrupciones

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER "LUGAR"
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
//*************************************************************************


int main(void)
{
	DDRA = 0x00;
	DDRC = 0xFF;
	
	PORTA = 0xFF;
	PORTC = 0x00;
	
	uint8_t lectura = 0;
    /* Codigo principal */
    while (1) 
    {
		lectura = PINA;
		
		if( lectura == 0b01101111)
		{
			PORTC = 0b11100111; //9
		}	
		else if( lectura == 0b01111111)
		{
			PORTC = 0b11111111; //8
		}
		else if( lectura == 0b10001111)
		{
			PORTC = 0b10000111; //7
		}
		else if( lectura == 0b10011111)
		{
			PORTC = 0b11111101; //6
		}
		else if( lectura == 0b10101111)
		{
			PORTC = 0b11101101; //5
		}
		else if( lectura == 0b10111111)
		{
			PORTC = 0b11100110; //4
		}
		else if( lectura == 0b11001111)
		{
			PORTC = 0b11001111; //3
		}
		else if( lectura == 0b11011111)
		{
			PORTC = 0b11011011; //2
		}
		else if( lectura == 0b11101111)
		{
			PORTC = 0b10000110; //1
		} 
		else if( lectura == 0b11111111)
		{
			PORTC = 0b10111111;
		}
		else
		{
			PORTC = 0b00000000;
		}
		
	}
}







