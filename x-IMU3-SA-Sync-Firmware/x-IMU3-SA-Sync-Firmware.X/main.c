/**
 * @file main.c
 * @author Seb Madgwick
 * @brief Main file.
 *
 * Device:
 * PIC10F322
 *
 * Compiler:
 * XC8 v2.35
 */

//------------------------------------------------------------------------------
// Configuration bits

#pragma config FOSC = INTOSC    // Oscillator Selection bits (INTOSC oscillator: CLKIN function disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config WDTE = SWDTEN    // Watchdog Timer Enable (WDT controlled by the SWDTEN bit in the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)
#pragma config LPBOR = ON       // Brown-out Reset Selection bits (BOR enabled)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)

//------------------------------------------------------------------------------
// Includes

#include "Delay.h"
#include <stdbool.h>
#include "UartTX.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Functions

void main(void) {

    // Select 16 MHz oscillator
    OSCCONbits.IRCF = 0b111;

    // Configure TX output
    ANSELAbits.ANSA1 = 0;
    TRISAbits.TRISA1 = 0;
    LATAbits.LATA1 = 1;

    // Configure sync input
    ANSELAbits.ANSA2 = 0;

    // Print firmware version
    Delay(DelayPeriod512ms);
    UartTXString("x-IMU3-SA-Sync v1.0\r\n");

    // Main program loop
    while (true) {
        static char polarity = '1';
        static char counter[] = "000000000";

        // Wait for rising/falling edge
        bool currentState = PORTAbits.RA2 == 1;
        static bool previousState;
        if (previousState == currentState) {
            continue;
        }
        previousState = currentState;

        // Write polarity
        UartTXByte(polarity);

        // Write comma
        UartTXByte(',');

        // Write counter
        UartTXString(counter);

        // Write termination
        UartTXByte('\r');
        UartTXByte('\n');

        // Update polarity
        if (polarity == '1') {
            polarity = '0';
        } else {
            polarity = '1';
        }

        // Increment counter
        char* digit = counter + sizeof (counter) - 2;
        while (true) {
            if (++*digit > '9') {
                *digit = '0';
                if (digit-- == counter) {
                    digit = counter + sizeof (counter) - 2;
                    *digit = '0' - 1;
                }
            } else {
                break;
            }
        }
    }
}

//------------------------------------------------------------------------------
// End of file
