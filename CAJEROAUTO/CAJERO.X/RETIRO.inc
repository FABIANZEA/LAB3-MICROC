RETIRO:
     ;-------------------------------------------------
    ;LA FUNCION DE ESTA RUTINA ES LA DESCONTAR EL DINERO QUE SE ENCUENTRA EN LA CUENTA
;----------------------------------------------------
    
    
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
LINEA14:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN14
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA14
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
LINEA15:
    MOVF    REG2,W
    CALL    LIN15
    MOVWF   REG1 
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA15


;-------------------------------------------------
    ;COLOCA EL CURSOR EN LA PRIMERA LINEA EN EL INICIO
;----------------------------------------------------
  
    MOVLW   0X80	
    MOVWF   REG1
    CALL    COMAND8
    
;-------------------------------------------------
    ;NO SALTA SI SE OPRIME UNA TECLA
;----------------------------------------------------
AS:
    MOVLW   0XFF
    MOVWF   TECLA
 
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    $-3  
     
;-------------------------------------------------
    ;SELECCION DE OPERACION
    ;1 RETIRO DE 5000
    ;2 RETIRO DE 10000
    ;3 RETIRO DE 15000
    ;4 RETIRO DE 20000
;----------------------------------------------------    
    
;-------------------------------------------------
    ;RUTINA PARA ASEGURARSE DE NO SALTAR SI SE OPRIME UNA TECLA QUE NO SEA UN NUMERO MAYOR A 4
;---------------------------------------------------- 
    MOVF    TECLA,W
    MOVWF   CAN
    MOVLW   0X05
    SUBWF   TECLA,W
    BTFSC   STATUS,C
    GOTO    AS   
 
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
 FAB:   
    MOVLW   0XFF
    MOVWF   TECLA
 
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    $-3 
    
    MOVLW   0X0B
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    RETIRO
    
    MOVLW   0X0C
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    FAB
    
    
    
    
;-------------------------------------------------
    ;SI TECLA ORPIMIDA ES 1 EL RETIRO ES DE 5000
;----------------------------------------------------    
    MOVLW   0X01
    XORWF   CAN,W
    BTFSS   STATUS,Z
    GOTO    $+2
    GOTO    CINCOMIL
;-------------------------------------------------
    ;SI TECLA ORPIMIDA ES 2 EL RETIRO ES DE 10000
;----------------------------------------------------     
    MOVLW   0X02
    XORWF   CAN,W
    BTFSS   STATUS,Z
    GOTO    $+2
    GOTO    DIEZMIL
;-------------------------------------------------
    ;SI TECLA ORPIMIDA ES 3 EL RETIRO ES DE 15000
;----------------------------------------------------     
    MOVLW   0X03
    XORWF   CAN,W
    BTFSS   STATUS,Z
    GOTO    $+2
    GOTO    QUINCEMIL
    
;-------------------------------------------------
    ;SI TECLA ORPIMIDA ES 4 EL RETIRO ES DE 20000
;----------------------------------------------------     
    MOVLW   0X04
    XORWF   CAN,W
    BTFSS   STATUS,Z
    GOTO    RETIRO
    GOTO    VEINTEMIL
    
CINCOMIL:
    MOVLW   0X05
    SUBWF   DINERO,W
    MOVWF   DINERO
    BTFSC   STATUS,C
    GOTO    TRANSA
    GOTO    SINSALDO
    

DIEZMIL:
    MOVLW   0X0A
    SUBWF   DINERO,W
    MOVWF   DINERO
    BTFSC   STATUS,C
    GOTO    TRANSA
    MOVLW   0X0A
    ADDWF   DINERO,W
    MOVWF   DINERO
    GOTO    SINSALDO
    
QUINCEMIL:
    MOVLW   0X0F
    SUBWF   DINERO,W
    MOVWF   DINERO
    BTFSC   STATUS,C
    GOTO    TRANSA
    MOVLW   0X0F
    ADDWF   DINERO,W
    MOVWF   DINERO
    GOTO    SINSALDO
    
    
VEINTEMIL:
    MOVLW   0X14
    SUBWF   DINERO,W
    MOVWF   DINERO
    BTFSC   STATUS,C
    GOTO    TRANSA
    MOVLW   0X14
    ADDWF   DINERO,W
    MOVWF   DINERO
    GOTO    SINSALDO
    
    
TRANSA:
;-------------------------------------------------
    ;BORRA Y REGRESA A CERO
;----------------------------------------------------
    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
;-------------------------------------------------
    ;MUESTRA MENSAJE TRANSACCION EXITOSA
;----------------------------------------------------

    
LINEA13S:
    CLRF    REG1
    MOVF    REG2,W
    CALL    LIN13
    MOVWF   REG1
    CALL    DATO8
    INCF    REG2
    BTFSS   REG2,4
    GOTO    LINEA13S
    
PPP:  
    MOVLW   0XFF
    MOVWF   TECLA
ZZZ:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    ZZZ
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR 
;---------------------------------------------------- 

    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    GOTO    PPP
    
SINSALDO:
   ;-------------------------------------------------
    ;BORRA Y REGRESA A CERO
;----------------------------------------------------
    MOVLW   0X01			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
    
    MOVLW   0X86			;BORRA Y REGRESA A CERO
    MOVWF   REG1
    CALL    COMAND8
;-------------------------------------------------
    ;MUESTRA MENSAJE SALDO INSUFICIENTE
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
    
    MOVLW   0XC2			;POSICIONA EN LA SEGUNDA LINEA EN EL ESPACIO 2
    MOVWF   REG1
    CALL    COMAND8
    CLRF    REG2
    
    MOVLW   'I'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'N'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'S'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'U'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'F'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'I'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'C'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'I'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'E'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'N'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'T'			
    MOVWF   REG1
    CALL    DATO8
    MOVLW   'E'			
    MOVWF   REG1
    CALL    DATO8
    
    
PPPP:  
    MOVLW   0XFF
    MOVWF   TECLA
ZZZZ:
    MOVLW   0XFF
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    ZZZZ
;-------------------------------------------------
    ;RETORNA A PEDIR EL TERCER DIGITO SI SE OPRIME LA TECLA DE BORRAR 
;---------------------------------------------------- 

    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    OPCION
    
    MOVLW   0X0D
    XORWF   TECLA,W
    BTFSC   STATUS,Z
    GOTO    INICIO
    GOTO    PPPP 
    
    