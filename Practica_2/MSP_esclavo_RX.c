//
//                                /|\  /|\
//                MSP430F5529     10k  10k     MSP430F5529
//                   esclavo       |    |         maestro
//             -----------------   |    |   -----------------
//           -|XIN  P3.0/UCB0SDA|<-|----+->|P3.0/UCB0SDA  XIN|-
//            |                 |  |       |                 |
//           -|XOUT             |  |       |             XOUT|-
//            |     P3.1/UCB0SCL|<-+------>|P3.1/UCB0SCL     |
//            |                 |          |                 |

#include <msp430.h>

/* Variables globales */
volatile unsigned char RXData;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Detenemos perro guardian
  P1DIR |= BIT0;                            //declaramos el led como salida
  P3SEL |= 0x03;                            // Asignamos 3.0 y 3.1 a USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
  UCB0I2COA = 0x48;                         // Own Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  UCB0IE |= UCRXIE;                         // Enable RX interrupt

  while (1)
  {
    __bis_SR_register(LPM0_bits + GIE);     // LPM0, Habilitamos interrupcion
    __no_operation();                       //

  }                                         //
}

// Funcion de servicio de interrupcin USCI_B0
#if defined(_TI_COMPILER_VERSION) || defined(IAR_SYSTEMS_ICC_)
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
#elif defined(_GNUC_)
void _attribute_ ((interrupt(USCI_B0_VECTOR))) USCI_B0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  switch(__even_in_range(UCB0IV,12))
  {
  case  0: break;                           // Vector  0: No interrupts
  case  2: break;                           // Vector  2: ALIFG
  case  4: break;                           // Vector  4: NACKIFG
  case  6: break;                           // Vector  6: STTIFG
  case  8: break;                           // Vector  8: STPIFG
  case 10:                                  // Vector 10: RXIFG
    RXData = UCB0RXBUF;                     // Se obtiene el dato del buffer RX
    /*Agregar condicion de comparación para encender led */
    if (UCB0RXBUF == 'a'){
        P1OUT |= BIT0;
    }else{
        P1OUT &= ~BIT0;
    }
    __bic_SR_register_on_exit(LPM0_bits);   // Exit LPM0
    break;
  case 12: break;                           // Vector 12: TXIFG
  default: break;
  }
}
