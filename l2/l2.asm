#include <p16f887.inc>

                LIST            P=16F887

                __config        _CONFIG1,b'1110000011100100'
                __config        _CONFIG2,b'1111100011111111'

                ORG             0X0

                BSF             STATUS,5                        ;Set Bank1

                MOVLW           B'00000001'                     ;Portd[0] -> In, Others out
                MOVWF           TRISD

                BCF             STATUS,5                        ;Set Bank0

;--------------------------------------------------------------------------------------------------

MAIN            BTFSC           PORTD,0                         ;If portd[0] != 0, GOTO BUZZ
                GOTO            BUZZ
                GOTO            MAIN


BUZZ            BSF             PORTD,1                         ;Turn on
                CALL            DELAY_3S
                BCF             PORTD,1                         ;Turn off
                CALL            DELAY_3S

                BTFSS           PORTD,0                         ;If portd[0] == 0, GOTO MAIN
                GOTO            MAIN
                GOTO            BUZZ

;--------------------------------------------------------------------------------------------------
;       Mcu runs with 4MHz oscillator, every instruction takes 4 osc pulses so every instruction 
;       takes 1 micro second. In order to wait for 3s, 3000000 instructions must be spent.
;--------------------------------------------------------------------------------------------------

CNT_3S          EQU             0X20                            ;Using general purpose registers
CNT_250MS       EQU             0X21                            ;for counting
CNT_1MS         EQU             0X22

;--------------------------------------------------------------------------------------------------

DELAY_3S        MOVLW           D'12'                           ;Setting outer loop counter
                MOVWF           CNT_3S
__DLY_3S        CALL            DELAY_250MS
                DECFSZ          CNT_3S
                GOTO            __DLY_3S
                RETURN

DELAY_250MS     MOVLW           D'249'                          ;Inner loop ~1.2ms so 249 is better 
                MOVWF           CNT_250MS
__DLY_250MS     CALL            DELAY_1MS                       ;(1, 2)
                DECFSZ          CNT_250MS                       ;(3)
                GOTO            __DLY_250MS                     ;(4, 5)
                RETURN

DELAY_1MS       MOVLW           D'249'                          ;(*1)   249us*4 + 4us = 1ms
                MOVWF           CNT_1MS                         ;(*2)
__DLY_1MS       NOP                                             ;(1)
                DECFSZ          CNT_1MS                         ;(2)
                GOTO            __DLY_1MS                       ;(3, 4)
                RETURN                                          ;(*3, *4)


END