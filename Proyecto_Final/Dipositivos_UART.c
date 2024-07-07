#include <msp430.h>
int i;
static const char mensaje[] = "ZZZZZZZZZZ";

void imprimir(const char mensaje[], int longitud);

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P4DIR |= BIT7; //Led rojo como salida
	P4SEL |= BIT5 | BIT4; //Activo la funcion Rx y Tx en P4.4 y P4.5, respectivamente.
	UCA1CTL1 |= UCSWRST; //Habilito el reset en la USCI
	UCA1CTL1 |= UCSSEL__SMCLK; //Conecta la fuente SMCLK a la USCI

	UCA1BR0 = 109; //Establece una velocidad de 9600 bps
	UCA1MCTL = UCBRS_2;
	UCA1CTL1 &= ~UCSWRST; //Se desconecta el reset
	UCA1IE |= UCRXIE; //Habilito la interrupcion en la recepcion

	__bis_SR_register(GIE);


	while(1){
	    imprimir(mensaje, sizeof(mensaje));

	    if(UCA1RXBUF == 'a')
	        P4OUT |= BIT7; //Encender Led
	    else
	        P4OUT &= ~BIT7; //Apagar Led
	}
	

}

void imprimir(const char mensaje[], int longitud){
    for(i=0; i<longitud; i++){
        UCA1TXBUF = mensaje[i];
        __delay_cycles(100000);
    }
}

#pragma vector =USCI_A1_VECTOR
__interrupt void UART (void)
{
    UCA1TXBUF = UCA1RXBUF; //Eco, el micro recive y la devuelve a la computadora
}
