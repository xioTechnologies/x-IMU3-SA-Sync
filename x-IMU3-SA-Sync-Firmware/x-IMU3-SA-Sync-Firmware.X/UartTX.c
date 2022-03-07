/**
 * @file UartTX.c
 * @author Seb Madgwick
 * @brief UART transmission for PIC10 devices.  Fixed at 115200 baud for 16 MHz.
 */

//------------------------------------------------------------------------------
// Includes

#include "UartTX.h"

//------------------------------------------------------------------------------
// Function declarations

void UartTX(void);

//------------------------------------------------------------------------------
// Variables

static volatile uint8_t uartData;
static volatile uint8_t uartCounter;
static volatile uint8_t uartDelay;

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Transmits byte.
 * @param byte Byte.
 */
void UartTXByte(const uint8_t byte) {
    uartData = byte;
    UartTX();
}

/**
 * @brief Transmits string.
 * @param string String.
 */
void UartTXString(const char* string) {
    while (*string != '\0') {
        UartTXByte(*string++);
    }
}

//------------------------------------------------------------------------------
// End of file
