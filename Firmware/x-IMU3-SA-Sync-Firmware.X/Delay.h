/**
 * @file Delay.h
 * @author Seb Madgwick
 * @brief Delay for PIC10 devices using sleep and watchdog timer.
 */

//------------------------------------------------------------------------------
// Definitions

/**
 * @brief Delay period.
 */
typedef enum {
    DelayPeriod1ms = (0 << 1) | 1,
    DelayPeriod2ms = (1 << 1) | 1,
    DelayPeriod4ms = (2 << 1) | 1,
    DelayPeriod8ms = (3 << 1) | 1,
    DelayPeriod16ms = (4 << 1) | 1,
    DelayPeriod32ms = (5 << 1) | 1,
    DelayPeriod64ms = (6 << 1) | 1,
    DelayPeriod128ms = (7 << 1) | 1,
    DelayPeriod256ms = (8 << 1) | 1,
    DelayPeriod512ms = (9 << 1) | 1,
    DelayPeriod1s = (10 << 1) | 1,
    DelayPeriod2s = (11 << 1) | 1,
    DelayPeriod4s = (12 << 1) | 1,
    DelayPeriod8s = (13 << 1) | 1,
    DelayPeriod16s = (14 << 1) | 1,
    DelayPeriod32s = (15 << 1) | 1,
    DelayPeriod64s = (16 << 1) | 1,
    DelayPeriod128s = (17 << 1) | 1,
    DelayPeriod256s = (18 << 1) | 1,
} DelayPeriod;

//------------------------------------------------------------------------------
// Function declarations

void Delay(const DelayPeriod period);

//------------------------------------------------------------------------------
// End of file
