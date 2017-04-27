
    ;-------------------------------------------------
    ;CONFIGURACION DE LA LCD 
;----------------------------------------------------
INI_LCD:
    CLRF    REG1
    CALL    Retardo_5ms
    
    MOVLW   0X38			;COMUNICACION A 8 BITS DOS LINEAS FUENTE 5X7
    MOVWF   REG1
    CALL    COMAND8
    
    MOVLW   0x0D
    MOVWF   REG1
    CALL    COMAND8		        ;ACTIVA DISPLAY

    MOVLW   0X06			;NO SE DESPLAZA, APUNTADOR SE INCREMENTA CON NUEVA ESCRITURA DE DATO
    MOVWF   REG1
    CALL    COMAND8	

    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
   
RETURN

;-------------------------------------------------
    ;RUTINA PARA ENVIO DE COMANDOS A LA LCD
;----------------------------------------------------
COMAND8
	BCF	PORTE,0
	GOTO	$+2
	
;-------------------------------------------------
    ;RUTINA PARA ENVIO DE DATOS A LA LCD
;----------------------------------------------------
DATO8
	BSF	PORTE,0
	MOVF	REG1,W
	MOVWF	PORTC
	BSF	PORTE,1
	CALL	Retardo_50ms
	BCF	PORTE,1
	CALL	Retardo_50ms
	RETURN






