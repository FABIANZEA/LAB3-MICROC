;-------------------------------------------------
    ;RUTINA PARA ESCOJER QUE TRANSACCION SE DESEA REALIZAR
;----------------------------------------------------
OPCION:
;-------------------------------------------------
    ;BORRA Y REGRESA A CERO
;----------------------------------------------------
VUELVE:    
    MOVLW   0X01			
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
;-------------------------------------------------
    ;MENSAJE EN LINEA UNO ESOJA OPERACION
;----------------------------------------------------

LINEA8:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN8
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA8
;-------------------------------------------------
    ;APUNTADOR EN LA LINEA 2
;----------------------------------------------------
  
    MOVLW   0XC0	
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
    CLRF    REG1

LINEA9:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN9
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA9 
    
;-------------------------------------------------
    ;COLOCA EL CURSOR EN LA PRIMERA LINEA EN EL 7 
;----------------------------------------------------
  
    MOVLW   0X86	
    MOVWF   REG1
    CALL    COMAND8  
;-------------------------------------------------
    ;NO SALTA SI SE OPRIME UNA TECLA
;----------------------------------------------------
AA:
    MOVLW   0XFF
    MOVWF   TECLA
 
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    $-3  
     
;-------------------------------------------------
    ;SELECCION DE OPERACION
    ;1 CAMBIO DE CONTRASEÑA
    ;2 RETIRO DE DINERO
    ;3 CONSULTAR SALDO
;----------------------------------------------------    
    
;-------------------------------------------------
    ;RUTINA PARA ASEGURARSE DE NO SALTAR SI SE OPRIME UNA TECLA QUE NO SEA UN NUMERO
;---------------------------------------------------- 
    MOVF    TECLA,W
    MOVWF   OP
    MOVLW   0X04
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    AA   
 
;-------------------------------------------------
    ;MUESTRA EN LCD EL NUMERO DE LA TECLA QUE SE OPRIMIO
;----------------------------------------------------     
    MOVF    TECLA,W
    CALL    LIN4
    MOVWF   REG1
    CALL    DATO8
 
;-------------------------------------------------
    ;RUTINA QUE NO PERMITE SALTAR HASTA INGRESAR UNA TECLA
    ;LAS TECLAS HABILITADAS SON ENTER BORRAR E INICIO
;----------------------------------------------------      
XXX:  
    MOVLW   0XFF
    MOVWF   TECLA
 
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    $-3 
    
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    VUELVE
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    VUELVE
    
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    XXX
    
    
    
    
;-------------------------------------------------
    ;SI TECLA ORPIMIDA ES 1 SALTA A LA RUTINA DE CAMBIO DE CONTRASEÑA
;----------------------------------------------------    
    MOVLW   0X01
    XORWF   OP,W
    BTFSS   STATUS,Z
    GOTO    $+2
    CALL    CAMBIAR_CLAVE
;-------------------------------------------------
    ;SI TECLA ORPIMIDA ES 2 SALTA A LA RUTINA DE RETIRO DE DINERO
;----------------------------------------------------     
    MOVLW   0X02
    XORWF   OP,W
    BTFSS   STATUS,Z
    GOTO    $+2
    CALL    RETIRO
;-------------------------------------------------
    ;SI TECLA ORPIMIDA ES 3 SALTA A LA RUTINA DE CONSULTA DE SALDO
;----------------------------------------------------     
    MOVLW   0X03
    XORWF   OP,W
    BTFSS   STATUS,Z
    GOTO    OPCION
    CALL    SALDO