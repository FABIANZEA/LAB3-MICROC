
    ;-------------------------------------------------
    ;LA FUNCION DE ESTA RUTINA ES LA DE CAMBIAR LA CLAVE DE INGRESO
;----------------------------------------------------
CAMBIAR_CLAVE:
    
    
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
LINEA11:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN11
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA11
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
LINEA12:
    MOVF    REG2,W
    CALL    LIN12
    MOVWF   REG1 
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA12
    
    MOVLW   0XC7	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8


;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;----------------------------------------------------  
BOR_1C:    
    MOVLW   0XFF
    MOVWF   TECLA
REP1C:  
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP1C  
 ;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_1C
    
;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL PRIMER DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;---------------------------------------------------- 
    
    MOVF    TECLA,W
    MOVWF   CLAVEC_0
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8

;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_2C: 
    MOVLW   0XFF
    MOVWF   TECLA
REP2C: 
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP2C   
    
;-------------------------------------------------
    ;RETORNA A PEDIR EL PRIMER DIGITO SI SE OPRIME LA TECLA DE BORRAR
;----------------------------------------------------  
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    TECLA2C 
    
    
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_1C
    
 ;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
TECLA2C:  
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_2C


;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL SEGUNDO DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;---------------------------------------------------- 
 
   
    MOVF    TECLA,W
    MOVWF   CLAVEC_1
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8
 
;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_3C:  
    MOVLW   0XFF
    MOVWF   TECLA
REP3C:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP3C
    
;-------------------------------------------------
    ;RETORNA A PEDIR EL SEGUNDO DIGITO SI SE OPRIME LA TECLA DE BORRAR
;----------------------------------------------------     
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    TECLA_3C 
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_2C
    
;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
TECLA_3C:
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_3C


;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL TERCER DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;----------------------------------------------------
    
    MOVF    TECLA,W
    MOVWF   CLAVEC_2
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8

;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_4C:  
    MOVLW   0XFF
    MOVWF   TECLA
REP4C:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP4C
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR 
;---------------------------------------------------- 
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    TECLA_4C 
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_3C    
;-------------------------------------------------
    ;RUTINA QUE PERMITE COMPROBAR QUE LA TECLA QUE SE HALLA ORPIMIDO NO SEA DIFERENTE A LA DE UN NUMERO
;----------------------------------------------------     
TECLA_4C:
    MOVLW   0X0A
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    BOR_4C


 
;-------------------------------------------------
    ;GUARDA EL VALOR DE LA TECLA EN EL CUARTO DIGITO DE LA CLAVE Y MUESTRA EL NUMERO EN LA LCD
;----------------------------------------------------
    
    MOVF    TECLA,W
    MOVWF   CLAVEC_3
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8
    
  
;-------------------------------------------------
    ;SALTA CUANDO SE OPRIMA UNA TECLA DEL TECLADO
;---------------------------------------------------- 
BOR_5C:
    MOVLW   0XFF
    MOVWF   TECLA
REP5C:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    REP5C
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR
;----------------------------------------------------     
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    SALIRAC
    
    MOVLW   0X10	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    GOTO    BOR_4C
;-------------------------------------------------
    ;TERMINA LA RUTINA CUANDO SE OPRIME LA TECLA ENTER Y RETORNA A LA FUNCION PRINCIPAL
;---------------------------------------------------- 
SALIRAC:
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    BOR_5C

;-------------------------------------------------
    ;BORRA Y REGRESA A CERO
;----------------------------------------------------
    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
;-------------------------------------------------
    ;MUESTRA MENSAJE DE CLAVE CAMBIADA
;----------------------------------------------------
LINEA13:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN13
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA13
    
PP:  
    MOVLW   0XFF
    MOVWF   TECLA
ZZ:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    ZZ
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR 
;---------------------------------------------------- 
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    GOTO    PP
    

