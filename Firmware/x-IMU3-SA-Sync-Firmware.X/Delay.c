/**
 * @file Delay.c
 * @author Seb Madgwick
 * @brief Delay for PIC10 devices using sleep and watchdog timer.
 */

//------------------------------------------------------------------------------
// Includes

#include "Delay.h"
#include <xc.h>

//------------------------------------------------------------------------------
// Functions

/**
 * @brief Delays for selected period.
 * @param period Period.
 */
void Delay(const DelayPeriod period) {
    WDTCON = period;
    SLEEP();
    WDTCONbits.SWDTEN = 0;
}

//------------------------------------------------------------------------------
// End of file
