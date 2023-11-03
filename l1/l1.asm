#include <p16f887.inc>

        LIST            p=16f887

        __config        _CONFIG1,b'1110000011100100'
        __config        _CONFIG2,b'1111100011111111'

        ORG             0x00

        BSF             STATUS,5                        ;From status register bank 1 is selected.

        MOVLW           b'00000101'
        MOVWF           TRISD                           ;TRISD setting portd 0 and 2 in, others out

        BCF             STATUS,5                        ;Bank 0 is selected again
        

        
LOOP:
        BTFSC           PORTD,0                         ;If portd[0] == 1 -> portd[1] = 1
        BSF             PORTD,1
        BTFSS           PORTD,0                         ;If portd[0] == 0 -> portd[1] = 0
        BCF             PORTD,1
        
        BTFSS           PORTD,2                         ;If portd[2] == 0 -> portd[3] = 1
        BSF             PORTD,3
        BTFSC           PORTD,2                         ;If portd[2] == 1 -> portd[3] = 0
        BCF             PORTD,3
        
        GOTO            LOOP
        
        END