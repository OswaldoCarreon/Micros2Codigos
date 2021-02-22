uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT);
uint8_t tecladoFuncion(volatile uint8_t *DDRT, volatile uint8_t *PORTT, volatile uint8_t *PINT);


//CONSIDERACIONES:
//Asigna de qué pines a qué pines están conectadas las filas de la matriz.
//Asigna de qué pines a que pines están conectadas las columnas de la matriz
uint8_t filas = 0, filasend = 1, columnas = 2, columnasend = 3;

//Una vez estén los pines asignados correctamente, entonces el código ya está listo para tomar el tamaño de la matriz correctamente
//NO ES NECESARIO MODIFICAR EL TAMAÑO DE LA MATRIZ, el tamaño se tomará conforme a los pines que asignaste anteriormente.
//Asigna los valores que la matriz debe tomar, si la matriz es más pequeña que 4x4, sólo llena los valores correspondientes al tamaño comenzando de la posición 0,0
volatile uint8_t teclado[4][4] = {	{1,6,0,0},
									{3,9,0,0},
									{0,0,0,0},
									{0,0,0,0} };



uint8_t cero_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (!(*LUGAR&(1<<BIT)));
}

uint8_t uno_en_bit(volatile uint8_t *LUGAR, uint8_t BIT)
{
	return (*LUGAR&(1<<BIT));
}


uint8_t tecladoFuncion(volatile uint8_t *DDRT, volatile uint8_t *PORTT, volatile uint8_t *PINT) {
	
	for(uint8_t i=filas; i<=filasend;i++){
		*DDRT |= (1<<i);		// definimos puerto para teclado
	}
		
	while(1) {
		
		*PORTT = 0b11111111;
		
		for (uint8_t fila = filas; fila <= filasend; fila++) {
			
			*PORTT = ~(1<<fila);
			_delay_us(2);
			
			for (uint8_t col = columnas; col <= columnasend; col++) {
				
				if (cero_en_bit(PINT,col)) {
					_delay_ms(100);
					while(cero_en_bit(PINT,col)) {}
					_delay_ms(100);
					return teclado[filasend-fila][columnasend-col];
				}
			}
		}
	}
}