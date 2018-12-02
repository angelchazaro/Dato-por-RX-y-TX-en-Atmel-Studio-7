/*
 * ATmega32 prueba TX RX.c
 *
 * Created: 26/01/2018 08:57:11 p. m.
 * Author : dx_ch
 */ 

// PARA UN CRISTAL DE 8 MHZ

#define  F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


/************************************************************************/
/*           FUNCIONES PARA LA TRANSMISIÓN DE DATOS POR LA USART		*/
/************************************************************************/
void USART_TxChar(char data)						/* Función para transmitir datos */
{
	UDR = data;
	while (!(UCSRA & (1<<UDRE)));
}

void USART_SendString(char *str)					/* Función para enviar cadena de caracteres */
{
	int i=0;
	while (str[i]!=0)
	{
		USART_TxChar(str[i]);						/* Envia cada uno de los caracteres */
		i++;
	}
}


int main(void)

{
	UBRRL = 51;		//configura los baudios de la comunicacion serial
	UCSRB = 0x98;	// se habilita la rx y tx y la interrupcion de datos completa.
	UCSRC = 0x86;	// modo asincrono, 8 bits de datos, sin paridad.
	sei();
	while (1)

	{
	}
}

// Interrupcion para la recepcion de datos,
// para atmgea32 USART_RXC_vect,
//USART_RX_vect para atmega328

ISR(USART_RXC_vect) // para ATmega32
{
	char DATO;
	DATO = UDR;
	
	if(DATO == '1')
	{
		PORTB|= 0x10;// codigo encender algo;
		USART_SendString("LED1_ON");
	}

	if (DATO == '2')
	{
		PORTB&= ~0x10;// codigo APAGAR algo;
		USART_SendString("LED1_OFF");
	}
}



