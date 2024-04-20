#include <msp430.h> 

//Este programa manda la tecla que se presione en la terminal.
//Para comprobar la correcta comunicacion, cuando se presione
//la tecla a, se enciende el led rojo, cuando se presione otra
//tecla, el led rojo se apaga.
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0; // ACTIVA EL LED COMO SALIDA
    P4SEL |= BIT4 |BIT5; // EL P4.4 ES TX Y EL P4.5 ES RX ESTAS SON INTERNAS
    UCA1CTL1 |= UCSWRST; // REALISE EL RESESETEO
    UCA1CTL1  |= UCSSEL__SMCLK; //SE CONETA EL RELOG
    UCA1BR0 |= 109; //se establese la velocidad de 9600 baudios por segundo
    UCA1MCTL |= UCBRS_2;
    UCA1CTL1 &= ~UCSWRST; // se desabilita el reset
    UCA1IE |= UCRXIE;
    //UCA1CTL0|= UCSPB|UCPEN|UCPAR; //Bit de paridad y dos bits de stop
    __bis_SR_register(GIE);
    
    //Programa para corroborar lectura en UART
    while (1)
    {
       if (UCA1RXBUF=='a')
       P1OUT |= BIT0;// ENCIENDO EL LED
       else
       P1OUT &= ~BIT0;//APAGO EL LED
    }
}


#pragma vector =USCI_A1_VECTOR //Interrupcion
__interrupt void UART (void)
{
    UCA1TXBUF = UCA1RXBUF ; //ECO

}
