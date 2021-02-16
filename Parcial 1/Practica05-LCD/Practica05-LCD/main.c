/*
 * Practica05-LCD.c
 *
 * Created: 11/02/2021 05:23:12 p. m.
 * Author : Oswal and Max
 */ 

#define  F_CPU 1000000UL
#include <avr/io.h>				//Librería general del Microcontrolador
#include <stdint.h>				//Para poder declarar varialbes especiales
#include <util/delay.h>			//Para poder hacer delays
//#include <avr/interrupt.h>	 //Para poder manejar interrupciones
#include "lcd.h"

//PROTOTIPADO DE FUNCIONES PARA PODER UTILIZARLAS DESDE CUALQUIER "LUGAR"
//*************************************************************************
uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t tecladoFuncion(volatile uint8_t *DDRT, volatile uint8_t *PORTT, volatile uint8_t *PINT);
/*volatile uint8_t teclado[4][4] = {	{10,9,8,7},
									{11,6,5,4},
									{12,3,2,1},
									{13,14,0,15}	};
*/
volatile uint8_t teclado[4][4] = {	{1,2,3,10},
									{4,5,6,11},
									{7,8,9,13},
									{12,0,14,15}	};
//*************************************************************************


int main(void)
{
	uint8_t tecla = 0, cont = 0;

	lcd_init(LCD_DISP_ON);
    lcd_gotoxy(16,0);
	//lcd_puts("o");
	
    while (1) 
    {
	    //tecla = tecladoFuncion(&DDRA, &PORTA, &PINA);
	    tecla = tecladoFuncion(&DDRB, &PORTB, &PINB);
		
		if(tecla < 10 && cont < 10) //Escribir un dígito
		{
			lcd_putc('0'+tecla);
			lcd_command(LCD_MOVE_DISP_LEFT); //para proteus debe ser a la derecha
			cont++;
			
		}
		else if(tecla == 15) //Eliminar todos los dígitos
		{
			lcd_clrscr();
			lcd_gotoxy(16,0);
			cont = 0;
		}
		
		else if(tecla == 12 && cont > 0) //Eliminar un dígito.
		{
			lcd_gotoxy(16+(cont-1),0);
			lcd_command(LCD_MOVE_DISP_RIGHT); //para proteus debe ser a la izquierda
			cont--;
		}
		
    }//endwhile
} //end main


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
					_delay_ms(100);
					while(cero_en_bit(PINT,col)) {}
					_delay_ms(100);
					return teclado[7-fila][col];
				}
			}
		}
	}
}