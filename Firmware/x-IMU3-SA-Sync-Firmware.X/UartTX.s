#include <xc.inc>

uartPin equ 1 ;LATA1

global _uartData
global _uartCounter
global _uartDelay

psect UartTX, local, class=CODE, delta=2

global _UartTX

_UartTX:
    movwf _uartData
    movlw 10 ;1 start bit, 8 data bits, 1 stop bit
    movwf _uartCounter
    bcf LATA, uartPin // start bit
    goto delay

nextBit:
    movf LATA, W
    andlw ~(1 << uartPin) ;clear tx pin bit of W
    btfsc _uartData, 0
    iorlw (1 << uartPin) ;set tx pin bit of W
    movwf LATA
    bsf STATUS, 0 ;set carry bit to be used as stop bit after 8th data bit
    rrf _uartData

delay:
    movlw 8 ;delay 26 cycles
    movwf _uartDelay
delayLoop:
    decfsz _uartDelay
    goto delayLoop
    decfsz _uartCounter
    goto nextBit
    return ;return 5 cycles before the stop bit completes
