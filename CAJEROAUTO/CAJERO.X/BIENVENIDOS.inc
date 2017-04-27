
BIENVENIDOS:
    CLRF   ERRORR
    CLRF   REG2
    
    MOVLW  0X01
    MOVWF  INTENTO
    
    
;-------------------------------------------------
    ;MUESTRA EL MENSAJE DE BIENVENIDOS EN LA FILA DE ARRIBA
;----------------------------------------------------
LINEA1:
    MOVF    REG2,W
    CALL    LIN1
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA1
    RETURN
    



