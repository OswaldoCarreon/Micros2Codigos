/*
 * Titulo
 *
 * Created: Fecha
 * Author : Nombre
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
void showCount(uint8_t valor);
uint8_t swapNibbles(uint8_t x);
//*************************************************************************


int main(void)
{
    DDRA = 0x00; //Establezco todo el puerto A como entrada
	PORTA = 0xFF; //Le pongo pull ups a todo el puerto
	
	DDRC = 0xFF;
	PORTC = 0;
	
	uint8_t contador = 0;
	
    while (1) 
    {
		if( cero_en_bit(&PINA,0) ){ // Si presionan el botón incremento.
			if(contador < 99) contador++;
			
			showCount(contador);
			_delay_ms(60);
			while( cero_en_bit(&PINA,0) ){}
			_delay_ms(60);
				
		}
		
		
		if( cero_en_bit(&PINA,7) ){ // Si presionan el botón decremento.
			if(contador > 0 ) contador--;
			
			showCount(contador);
			_delay_ms(60);
			while( cero_en_bit(&PINA,7) ){}
			_delay_ms(60);
			
			
		}
		
    }
}

void showCount(uint8_t valor){
	uint8_t decenas = valor/10;
	uint8_t unidades = valor%10;
	
	unidades = swapNibbles(unidades);
	
	decenas = decenas ^ unidades;
	PORTC = decenas;
}



 
uint8_t swapNibbles(uint8_t x)
{
    return ( (x & 0x0F)<<4 | (x & 0xF0)>>4 );
}



uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (*LUGAR&(1<<BIT));
}