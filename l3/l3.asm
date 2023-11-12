        INCLUDE        "P16F887.INC"
        LIST            P=16F887

        __config        _CONFIG1,b'1110000011100001' 
        __config        _CONFIG2,b'1111100011111111'

        ORG             0X00
        GOTO            MAIN
        
        ORG             0X04
        GOTO            INTERRUPT

MAIN
        BANKSEL         ANSEL                   ;Digital io
        CLRF            ANSEL                   ;Analog off
        CLRF            ANSELH

        BANKSEL         OPTION_REG              ;Setup timer0 
        MOVLW           B'11000111'             ;prescalar 1:256
        MOVWF           OPTION_REG

        MOVLW           B'10100000'             ;Enable interrupt
        MOVWF           INTCON

        BANKSEL         TRISB                   ;PORTB all output
        CLRF            TRISB

        BANKSEL         PORTB
        CLRF            PORTB

CNT0    EQU             0X20                    ;Counter
        MOVLW           0X0F                    ;Tmr0 inc once every 256us
        MOVWF           CNT0                    ;256*256us*15 is about 1 second

LOOP
        GOTO            LOOP

INTERRUPT                                       ;Called when tmr0 overflows
        BCF             INTCON,2                ;Clear tmr0 overflow indicator
        DECFSZ          CNT0                    ;Check countdown
        RETFIE
        MOVLW           0X0F                    ;Reset countdown
        MOVWF           CNT0
        MOVLW           0X01
        XORWF           PORTB                   ;Toggle
        RETFIE
END