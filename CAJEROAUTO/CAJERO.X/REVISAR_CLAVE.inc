;-------------------------------------------------
    ;RUTINA UTLIZADA PARA COMPROBAR SI LA CONTRASEÑA ES CORRECTA
    ;Y COMPRUEBA SI LA CONTRASEÑA ES INGRESADA MAL 4 VECES PARA BLOQUEAR EL CAJERO
;----------------------------------------------------
    
REVISAR_CLAVE:
    CLRF   REG1
    CLRF   REG2
;-------------------------------------------------
    ;COMPRUEBA DIGITO A DIGITO SI LA CLAVE ES CORRECTA
;----------------------------------------------------
DIGITO0:
    MOVF  CLAVE_0,W
    XORWF CLAVEC_0,W
    BTFSS STATUS,Z
    GOTO  MAL
    
DIGITO1:
    MOVF  CLAVE_1,W
    XORWF CLAVEC_1,W
    BTFSS STATUS,Z
    GOTO  MAL   

DIGITO2:
    MOVF  CLAVE_2,W
    XORWF CLAVEC_2,W
    BTFSS STATUS,Z
    GOTO  MAL 
    
DIGITO3:
    MOVF  CLAVE_3,W
    XORWF CLAVEC_3,W
    BTFSS STATUS,Z
    GOTO  MAL

    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
;-------------------------------------------------
    ;SI LA CONTRASEÑA ES CORRECTA MUESTRA EL MENSAJE CONFIRMANDOLO
    ;LINEA 1
;----------------------------------------------------
LINEA5:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN5
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA5


RETURN
 ;-------------------------------------------------
    ;CONTRASEÑA ES INCORRECTA AUMENTA EL REGISTRO ERROR
    ;COMPRUEBA SI HAN INGRESADO LA CONTRASEÑA MAL 4 VECES
;----------------------------------------------------     
MAL:
    INCF   INTENTO
    INCF   ERRORR
    MOVLW  0X04
    XORWF  ERRORR,W
    BTFSC  STATUS,Z
    GOTO   BLOQUEO
    
    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
    CLRF    REG1
;-------------------------------------------------
    ;MUESTRA EL MENSAJE DE CONTRASEÑA INCORRECTA;
    ;EN LA PRIMERA LINEA
;---------------------------------------------------- 
LINEAS5:
    
    MOVF    REG2,W
    CALL    LIN5
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEAS5
    
    MOVLW   0X86	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    
    MOVLW   0X49
    MOVWF   REG1
    CALL    DATO8
    
    MOVLW   0X4E
    MOVWF   REG1
    CALL    DATO8
    
    MOVLW   0XC0	;APUNTADOR A LINEA 2 POSICION CERO
    MOVWF   REG1
    CALL    COMAND8
    
    CLRF    REG2
    CLRF    REG1
;-------------------------------------------------
    ;LINEA DOS, MUESTRA EL NUMERO DE INTENTOS QUE QUEDAN
;----------------------------------------------------    
LINEA6:
    MOVF    REG2,W
    CALL    LIN6
    MOVWF   REG1 
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA6
  
;-------------------------------------------------
    ;NO SALTA HASTA INGRESAR ENTER POR TECLADO
;----------------------------------------------------     
    MOVLW   0XFF
    MOVWF   TECLA
REPE: 
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    REPE
 
;-------------------------------------------------
    ;VA A LA RUTINA A PEDIR NUEVAMENTE LA CLAVE Y RETORNA A REVISAR NUEVAMENTE LA CONTRASEÑA
;---------------------------------------------------- 
    CALL    CLAVE
    GOTO    REVISAR_CLAVE

;-------------------------------------------------
    ;BORRA Y REGRESA A CERO LCD
;----------------------------------------------------     
BLOQUEO:
    MOVLW   0X01			
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
;-------------------------------------------------
    ;MUESTRA EL MENSAJE DE CAJERO BLOQUEADO
;---------------------------------------------------- 
LINEA7:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN7
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA7
;-------------------------------------------------
    ;CUANDO SE OPRIMA LA TECLA INTRO REINICIA EL PROGRAMA
;----------------------------------------------------    
    MOVLW   0XFF
    MOVWF   TECLA
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    $-3
    GOTO    INICIO
    
 
