;--------------------------------------
    ;CONFIGURACION DE PUERTOS Y DE BOTON PARA EL PUERTO B
;--------------------------------------
CONFIGURACION:
  BANKSEL  OSCCON
  MOVLW    0XF1
  MOVWF    OSCCON
  MOVLW    0XF0
  MOVWF    TRISB
  CLRF     TRISC
  CLRF     TRISE
  BANKSEL  ANSELH
  CLRF     ANSELH
  CLRF     ANSEL
  BSF      INTCON,7
  BSF      INTCON,3
  BANKSEL  OPTION_REG
  BCF      OPTION_REG,7
  BANKSEL  WPUB
  MOVLW    0XF0
  MOVWF    WPUB
  MOVWF    IOCB
  BANKSEL  PORTA
  MOVLW    0XF0
  MOVWF    PORTB
  CLRF     PORTC
  CLRF     PORTE
  CLRF     TECLA
  
  
;-------------------------------------------------
    ;ASIGNA VALORES INICIALES A LOS CUATRO DIGITOS DE LA CLAVE
;----------------------------------------------------
    MOVLW  0X00
    MOVWF  CLAVEC_0
    MOVLW  0X01
    MOVWF  CLAVEC_1
    MOVLW  0X02
    MOVWF  CLAVEC_2
    MOVLW  0X03
    MOVWF  CLAVEC_3
    
    MOVLW  0XC8 
    MOVWF  DINERO
    RETURN
