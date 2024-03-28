//-----------------------------
// Title: Temperature Control
//-----------------------------
// Purpose: A temperature sensor senses the temperature of a given object. The 
//	    User will input their desiered temperature. Then the circuit will
//	    Control specified temperature either turning on cooling or heating
//	    fan. In this case we will be using an LED to represent the cooling
//	    and heating fan.
// Dependencies: AssemblyConfig.inc
// Compiler: MPLAB X IDE v6.20
// Author: Calvin Pereira
// OUTPUTS: Outputs to two LEDS PORTD1 and PORTD2
//	    PORTD1 - Signifies cooling fan
//	    PORTD2 - Signifies hot air blower
// INPUTS: User will input their desired temperature through a keypad
// Versions:
//  	V1.0: 03/06/2024 - First version 
//  	
//-----------------------------

#include ".\newAsmTemplate.inc"
#include <xc.inc>
    
;----------------
; PROGRAM INPUTS
;----------------
measuredTempInput   equ 	25		; Input for measured from sensor
refTempInput	    equ		25		; Input from user

;----------------
; REGISTERS
;----------------
measuredTempREG	    equ 	20h		; Setting reg 20 to store measured temp
refTempREG	    equ		21h		; Setting reg 21 to store reference temp
	    


;----------------
; PROGRAM OUTPUTS
;----------------
DCrefTempA	    equ		0x60		; Used to store decimal value of Refernece Temp
DCrefTempB	    equ		0x61		; Used to store decimal value of Refernece Temp
DCrefTempC	    equ		0x62		; Used to store decimal value of Refernece Temp
    
DCmesTempA	    equ		0x70		; Used to store decimal value of Measured Temp
DCmesTempB	    equ		0x71		; Used to store decimal value of Measured Temp
DCmesTempC	    equ		0x72		; Used to store decimal value of Measured Temp
    
#define		    HEATER      PORTD,2		; Sets PORTD 2 to the heater LED
#define		    COOLER	PORTD,1		; Sets PORTD 1 to the coller LED
	   
	   
;----------------
; Main Program
;----------------
	    PSECT absdata,abs,ovrld
	    
	    org 0
	    
	    GOTO START
	    
	    org 0020H

START:
    
    MOVLW   0b11111100
    MOVWF   TRISD, 0
    MOVLW   measuredTempInput
    MOVWF   measuredTempREG
    MOVLW   refTempInput
    MOVWF   refTempREG
    
    MOVFF   measuredTempREG, WREG
    GOTO    PPTEMPCHECK
    
PPTEMPCHECK:
    MOVFF   measuredTempREG, WREG
    
    CPFSEQ refTempREG, 0
    GOTO LED_OFF
    
    CPFSLT  0x21, 1
    GOTO LED_HOT
    
    CPFSGT refTempREG, 1
    GOTO LED_COOL
    
    

    
LED_HOT:
    BSF     COOLER, 0 ; Set PORTD,1 (Cooling LED)
    BCF     HEATER, 0 ; Clear PORTD,2 (Heater LED)
    GOTO    PPTEMPCHECK

    
LED_COOL:
    BSF     COOLER, 0 ; Set PORTD,2 (Cooling LED)
    BCF     HEATER, 0 ; Clear PORTD,1 (Heater LED)
    GOTO    PPTEMPCHECK

    
LED_OFF:
    BCF     COOLER, 0 ; Clear PORTD,1 (Cooling LED)
    BCF     HEATER, 0 ; Clear PORTD,2 (Heater LED)
    GOTO    PPTEMPCHECK


	
