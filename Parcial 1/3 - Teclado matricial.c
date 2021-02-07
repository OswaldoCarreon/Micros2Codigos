/*Practica03-TecladoMatricial.c
 * Created: 04/02/2021 06:15:21 p. m.
 * Author : Oswal*/ 

#define  F_CPU 1000000UL
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
//#include <avr/interrupt.h>	 //Para poder manejar interrupciones


uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t tecladoFuncion(volatile uint8_t *DDRT, volatile uint8_t *PORTT, volatile uint8_t *PINT);


volatile uint8_t teclado[4][4] = {	{12,9,8,7},
									{11,6,5,4},
									{10,3,2,1},
									{15,14,0,13} };


int main(void)
{
	uint8_t lectura = 0, salida1 = 0, salida2 = 0, cont = 0;
	
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTC = 0x00;
	PORTD = 0x00;
	 
    while (1) 
    {
		lectura = tecladoFuncion(&DDRA, &PORTA, &PINA);

		if(lectura < 10){
			//Para los ultimos 2 dígitos, va a ser un OR de (lo que tengo en los primeros 2 digitos recorrido a la derecha 4 veces) con (lo que ya tengo en los últimos dos dígitos recorrido a la izquierda 4 veces)
			//Esta acción se comineza a hacer hasta que se han presionado 3 dígitos.
			cont++;
			if(cont>2){
				salida2 = (salida1>>4) | (salida2<<4);
				PORTD = salida2;
			}
			//Para los primeros dos dígitos sólo hay que recorrer a laizquierda 4 veces y hacer un OR con lo que se leyó:
			salida1 = salida1<<4;
			salida1 = salida1 | lectura;
			PORTC = salida1;
			
		} else {
			salida1 = salida2 = cont = 0;
			PORTC = salida1;
			PORTD = salida2;
		}
		
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

uint8_t tecladoFuncion(volatile uint8_t *DDRT, volatile uint8_t *PORTT, volatile uint8_t *PINT) {
	
	*DDRT = (1<<7)|(1<<6)|(1<<5)|(1<<4);		// definimos puerto para teclado
	
	while(1) {
		
		*PORTT = 0b11111111;
		
		for (uint8_t fila = 7; fila > 3; fila--) {
			
			*PORTT = ~(1<<fila);
			_delay_us(2);
			
			for (uint8_t col = 0; col < 4; col++) {
				if (cero_en_bit(PINT,col)) {
					_delay_us(60);
					while(cero_en_bit(PINT,col)) {}
					_delay_us(60);
					return teclado[7-fila][col];
				}
			}
		}
	}
}