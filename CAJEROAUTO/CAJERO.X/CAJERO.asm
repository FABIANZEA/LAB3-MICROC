;----------------------------------------------------
    ;UNIVERSIDAD PEDAGOGICA Y TECNOLOGICA DE COLOMBIA
    ;ESCUELA DE INGENIERIA ELECTRONICA
    ;MICROCONTROLADORES PRIMER SEMESTRE 2017
    ;LABORATORIO #3 CAJERO AUTOMATICO
    ;FABIAN STEVEN ZEA GONZALEZ
    ;201210733
    ;JHONATAN REINALDO GOMEZ PESCA
    ;201210146
    
lIST p=16f887
#include "p16f887.inc"


; CONFIG1
; __config 0xEFF2
 __CONFIG _CONFIG1, _FOSC_HS & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_OFF 
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF
 
 CBLOCK 0X20
 REG1
 REG2
 W_V
 STATUS_V
 S_W
 S_STATUS
 TECLA
 CLAVE_0
 CLAVE_1
 CLAVE_2
 CLAVE_3
 CLAVEC_0
 CLAVEC_1
 CLAVEC_2
 CLAVEC_3
 ERRORR
 INTENTO
 OP
 DINERO
 CAN
 RESTAR
 ACAMBIAR 
 DECENAS
 CENTENAS
 ENDC
 
 ORG .0
 
    GOTO START

ORG .4
    GOTO INTERRUPCION
    
;-------------------------------------------------------
    ;TABLAS DE MENSAJES
;-------------------------------------------------------
LIN1
    ADDWF	PCL,1
    DT  "--BIENVENIDOS---"
    
LIN2
    ADDWF	PCL,1
    DT  "INGRESE LA CLAVE"  
LIN3
    ADDWF	PCL,1
    DT  "****   INTENTO: "
LIN4
    ADDWF  PCL,1
    RETLW  0X30
    RETLW  0X31
    RETLW  0X32
    RETLW  0X33
    RETLW  0X34
    RETLW  0X35
    RETLW  0X36
    RETLW  0X37
    RETLW  0X38
    RETLW  0X39
    RETLW  0X41
    
LIN5
    ADDWF  PCL,1
    DT  "CLAVE   CORRECTA"

LIN6
    ADDWF  PCL,1
    DT  "INTENTO DE NUEVO"

LIN7
    ADDWF  PCL,1
    DT  "CAJERO BLOQUEADO"
LIN8
    ADDWF  PCL,1
    DT  "SE.OP:  1.CA/CLA"
    
LIN9
    ADDWF  PCL,1
    DT  "2.RETIRO 3.SALDO"
    
LIN10
    ADDWF  PCL,1
    DT  "OPCION NO VALIDA"  
LIN11
    ADDWF  PCL,1
    DT  "INGRESE LA NUEVA"
LIN12
    ADDWF  PCL,1
    DT  "CLAVE: ****     "
    
LIN13
    ADDWF  PCL,1
    DT  "OPERACIONEXITOSA"
    
LIN14
    ADDWF  PCL,1
    DT  "  1$5000 2$10000"
    
LIN15
    ADDWF  PCL,1
    DT  "3$15000  4$20000"   
    
;-------------------------------------------------------------------
 
 START:
 
    CALL   CONFIGURACION
INICIO:     
    CALL   INI_LCD
    CALL   BIENVENIDOS
;-------------------------------------------------
    ;SALTA CUANDO SE OPRIME LA TECLA DE SIGUIENTE
;----------------------------------------------------
    MOVLW   0XFF
    MOVWF   TECLA
LOOP:
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    LOOP
    
    CALL    CLAVE
    CALL    REVISAR_CLAVE
    
    MOVLW   0XFF
    MOVWF   TECLA
    
    MOVLW   0X0F
    XORWF   TECLA,W
    BTFSS   STATUS,Z
    GOTO    $-3
    CALL    OPCION

  
    
;---------------------------
    ;RUTINA DE INTERRUPCION PARA EL TECLADO
;---------------------------
 INTERRUPCION:
    BCF     INTCON,GIE    ;DESABILITA INTERRUPCIONES
    CALL    PUSH
    BTFSS   INTCON,0      
    GOTO    UN
    MOVLW   0XF0
    MOVWF   PORTB
    CALL    Retardo_5ms
    MOVLW   0XF0
    XORWF   PORTB,W
    BTFSS   STATUS,Z
    CALL    TECLADO
  
;---------------------------
    ;DESACTIVA INTERRUPCIONES GLOBALES
;---------------------------
    
UN:
    MOVLW 0XF0
    MOVWF PORTB
    BCF   INTCON,0
    CALL POP
    RETFIE
    
;---------------------------
    ;GUARDA LOS DATOS EN LOS REGISTROS W Y REGISTROS STATUS
;---------------------------
PUSH:
    MOVWF  W_V
    MOVF   STATUS,W
    MOVWF  STATUS_V
    RETURN
POP:
    MOVF   W_V,W
    MOVF   STATUS_V,W
    MOVWF  STATUS
    RETURN
TECLADO:
;---------------------------------
     ;VERIFICA COLUMNA 1  DERECHA - IZQUIERDA 
;---------------------------------
    MOVLW  0XFE
    MOVWF  PORTB
    
    BTFSC  PORTB,7
    GOTO   $+4
    MOVLW  0X0F
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,6
    GOTO   $+4
    MOVLW  0X0B
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,5
    GOTO   $+4
    MOVLW  0X0C
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,4
    GOTO   $+4
    MOVLW  0X0D
    MOVWF  TECLA
    RETURN
;---------------------------------
     ;VERIFICA COLUMNA 2  DERECHA - IZQUIERDA   
;---------------------------------
    MOVLW  0XFD
    MOVWF  PORTB
    
    BTFSC  PORTB,7
    GOTO   $+4
    MOVLW  0X03
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,6
    GOTO   $+4
    MOVLW  0X06
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,5
    GOTO   $+4
    MOVLW  0X09
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,4
    GOTO   $+4
    MOVLW  0X0A
    MOVWF  TECLA
    RETURN
;---------------------------------
     ;VERIFICA COLUMNA 3  DERECHA - IZQUIERDA 
;---------------------------------
    MOVLW  0XFB
    MOVWF  PORTB
    
    BTFSC  PORTB,7
    GOTO   $+4
    MOVLW  0X02
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,6
    GOTO   $+4
    MOVLW  0X05
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,5
    GOTO   $+4
    MOVLW  0X08
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,4
    GOTO   $+4
    MOVLW  0X00
    MOVWF  TECLA
    RETURN
;---------------------------------
     ;VERIFICA COLUMNA 4  DERECHA - IZQUIERDA 
;---------------------------------
    MOVLW  0XF7
    MOVWF  PORTB
    
    BTFSC  PORTB,7
    GOTO   $+4
    MOVLW  0X01
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,6
    GOTO   $+4
    MOVLW  0X04
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,5
    GOTO   $+4
    MOVLW  0X07
    MOVWF  TECLA
    RETURN
    
    BTFSC  PORTB,4
    GOTO   $+4
    MOVLW  0X0E
    MOVWF  TECLA
    RETURN

    		
;--------------------------------------
    ;LIBRERIAS .INC
;-----------------------------------
#INCLUDE "CONFIGURACION.inc"
#INCLUDE "INI_LCD.inc"
#INCLUDE "BIENVENIDOS.inc"
#INCLUDE "CLAVE.inc"
#INCLUDE "REVISAR_CLAVE.inc"
#INCLUDE "OPCION.inc"
#INCLUDE "CAMBIAR_CLAVE.inc"
#INCLUDE "RETIRO.inc"   
#INCLUDE "SALDO.inc" 
#INCLUDE "Retardos.inc"

END
    


