SALDO:
     
;-----------------------------------------------
    ;CONVERSOR DEL SALDO A BCD DE UNIDADES, DECENAS Y CENTENAS
    ;PARA PODER VISUALIZAR DIGITO A DIGIO
CONVERSOR_BCD:
    CLRF     ACAMBIAR
    CLRF     DECENAS
    CLRF     CENTENAS
    MOVF     DINERO,W
    MOVWF    ACAMBIAR

BCD_ALTO1:
    MOVF     ACAMBIAR,W
    MOVLW    .100
    SUBWF    ACAMBIAR,F
    BTFSS    STATUS,C
    GOTO     SUMA_CIEN1
    INCF     CENTENAS
    GOTO     BCD_ALTO1
    
SUMA_CIEN1:
    MOVF    ACAMBIAR,W
    MOVLW   .100
    ADDWF   ACAMBIAR,F
    MOVF    ACAMBIAR,W       
    
BCD_BAJO1:
    MOVF    ACAMBIAR,W
    MOVLW   .10        ;MOVER 10 AL ACUMULADOR  W
    SUBWF   ACAMBIAR,f  ;RESTA ENTRE EL REGISTRO ACAMBIAR Y 100
    BTFSS   STATUS,C   ;SALTO SI EL CARRY ESTA EN 1
    GOTO    SUMA_DIEZ1
    INCF    DECENAS    ;INCREMENTO DEL VALOR DEL REGISTRO UNIDECE
    GOTO    BCD_BAJO1
SUMA_DIEZ1:
    
    MOVF    ACAMBIAR,W
    MOVLW   .10
    ADDWF   ACAMBIAR,F
;---------------------------------------------
    ;VERIFICA SI LA CUENTA TIENE FONDOS
 ;---------------------------------------------------
    MOVLW  0X00
    XORWF  CENTENAS,W
    BTFSC  STATUS,Z
    GOTO   $+2
    GOTO   MENSAJES_CENTENAS
    
    MOVLW  0X00
    XORWF  DECENAS,W
    BTFSC  STATUS,Z
    GOTO   $+2
    GOTO   MENSAJES_CENTENAS
    
    MOVLW  0X00
    XORWF  ACAMBIAR,W
    BTFSS  STATUS,Z
    GOTO   MENSAJES_CENTENAS
    GOTO   SALDO_INSUFICIENTE  
  
MENSAJES_CENTENAS:      
    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2   
;-------------------------------------------------
    ;MUESTRA MENSAJE SALDO DISPONIBLE
;----------------------------------------------------
    MOVLW   'S'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'A'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'L'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'D'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'O'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   ':'			
    MOVWF   REG1
    CALL    DATO8
    
    MOVLW   ' '			
    MOVWF   REG1
    CALL    DATO8

    MOVLW   '$'			
    MOVWF   REG1
    CALL    DATO8

    MOVF    CENTENAS,W
    CALL    LIN4
    MOVWF   REG1 
    CALL    DATO8
    
    MOVF    DECENAS,W
    CALL    LIN4
    MOVWF   REG1 
    CALL    DATO8
    
    MOVF    ACAMBIAR,W
    CALL    LIN4
    MOVWF   REG1 
    CALL    DATO8
    
    MOVLW   '0'			
    MOVWF   REG1
    CALL    DATO8
    
    MOVLW   '0'			
    MOVWF   REG1
    CALL    DATO8
    
    MOVLW   '0'			
    MOVWF   REG1
    CALL    DATO8
    GOTO    HH
    
    
SALDO_INSUFICIENTE:
    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
    
    MOVLW   'S'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'I'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'N'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   ' '			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'F'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   '0'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'N'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'D'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'O'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'S'			
    MOVWF   REG1
    CALL    DATO8
    
HH:  
    MOVLW   0XFF
    MOVWF   TECLA
JJ:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    JJ
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR 
;---------------------------------------------------- 

    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
 
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    GOTO    HH 