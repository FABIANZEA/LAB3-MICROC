CLAVE:
    
;-------------------------------------------------
    ;BORRA Y REGRESA A CERO
;----------------------------------------------------
    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
;-------------------------------------------------
    ;MUESTRA MENSAJE DE INGRESE CONTRASEÑA
;----------------------------------------------------
LINEA2:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN2
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA2
;-------------------------------------------------
    ;APUNTADOR A LINEA 2 POSICION CERO
;----------------------------------------------------

    MOVLW   0XC0	
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
    CLRF    REG1
 
;-------------------------------------------------
    ;MUESTRA EL NUMERO DE VECES QUE SE HA INTRODUCIDO LA CONTRASEÑA  **** EN LA FILA 2
;----------------------------------------------------
LINEA3:
    MOVF    REG2,W
    CALL    LIN3
    MOVWF   REG1 
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA3
    
    MOVLW   0XCF	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    
    MOVF    INTENTO,W
    CALL    LIN4
    MOVWF   REG1 
    CALL    DATO8

;-------------------------------------------------
    ;APUNTADOR A LINEA 2 POSICION 0
;----------------------------------------------------    
    MOVLW   0XC0	
    MOVWF   REG1
    CALL    COMAND8

;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;----------------------------------------------------  
BOR_1:    
    MOVLW   0XFF
    MOVWF   TECLA
REP1:  
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP1  
 ;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_1
    
;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL PRIMER DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;---------------------------------------------------- 
    
    MOVF    TECLA,W
    MOVWF   CLAVE_0
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8

;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_2: 
    MOVLW   0XFF
    MOVWF   TECLA
REP2: 
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP2   
    
;-------------------------------------------------
    ;RETORNA A PEDIR EL PRIMER DIGITO SI SE OPRIME LA TECLA DE BORRAR
    ;SI SE OPRIME LA TECLA INICIO REINICIA EL PROGRAMA
;----------------------------------------------------  
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    TECLA2 
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_1
    
 ;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
TECLA2:  
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_2


;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL SEGUNDO DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;---------------------------------------------------- 
 
   
    MOVF    TECLA,W
    MOVWF   CLAVE_1
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8
 
;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_3:  
    MOVLW   0XFF
    MOVWF   TECLA
REP3:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP3
    
;-------------------------------------------------
    ;RETORNA A PEDIR EL SEGUNDO DIGITO SI SE OPRIME LA TECLA DE BORRAR
    ;SI SE OPRIME LA TECLA INICIO REINICIA EL PROGRAMA
;----------------------------------------------------     
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    TECLA_3 
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_2
    
;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
TECLA_3:
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_3


;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL TERCER DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;----------------------------------------------------
    
    MOVF    TECLA,W
    MOVWF   CLAVE_2
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8

;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_4:  
    MOVLW   0XFF
    MOVWF   TECLA
REP4:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP4
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR 
    ;SI SE OPRIME LA TECLA INICIO REINICIA EL PROGRAMA
;---------------------------------------------------- 
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    TECLA_4 
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_3    
;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
TECLA_4:
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_4


 
;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL CUARTO DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;----------------------------------------------------
    
    MOVF    TECLA,W
    MOVWF   CLAVE_3
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8
    
  
;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_5:
    MOVLW   0XFF
    MOVWF   TECLA
REP5:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP5
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR
    ;SI SE OPRIME LA TECLA INICIO REINICIA EL PROGRAMA
;----------------------------------------------------     
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    SALIRA
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_4
;-------------------------------------------------
    ;TERMINA LA RUTINA CUANDO SE OPRIME LA TECLA ENTER Y RETORNA A LA FUNCION PRINCIPAL
    ;SI SE OPRIME LA TECLA INICIO REINICIA EL PROGRAMA
;---------------------------------------------------- 
SALIRA:   
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    BOR_5
    RETURN
    
    
 
    

    
    


