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
measuredTempInput   equ 	45		; Input for measured from sensor
refTempInput	    equ		25		; Input from user

;----------------
; REGISTERS
;----------------
measuredTempREG	    equ 	0x20		; Setting reg 20 to store measured temp
refTempREG	    equ		0x21		; Setting reg 21 to store reference temp
	    


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
	    org 0

START:
    
    MOVLW   0b11111100
    MOVWF   TRISD, 0
    MOVFF   measuredTempInput, measuredTempREG
    MOVFF   refTempInput,refTempREG
    MOVFF   measuredTempREG, WREG		; Move contents of measuredTempREG to WREG

    CPFSEQ  refTempREG, 0
    GOTO    LED_OFF
    
    CPFSGT refTempREG, 0
    GOTO   LED_HOT
    
    CPFSLT refTempREG, 0
    GOTO   LED_COOL

    
LED_HOT:
    ; Code for when the temperature is hot
    ; Example: Turn on the hot air blower LED
    BSF     HEATER, 0 ; Set PORTD,2 (Heater LED)
    BCF     COOLER, 1 ; Clear PORTD,1 (Cooling LED)
    GOTO    START ; Jump to the end of LED control
    
LED_COOL:
    ; Code for when the temperature is cool
    ; Example: Turn on the cooling fan LED
    BSF     COOLER, 0 ; Set PORTD,1 (Cooling LED)
    BCF     HEATER, 1 ; Clear PORTD,2 (Heater LED)
    GOTO    START ; Jump to the end of LED control
    
LED_OFF:
    ; Code for when the temperature is at the desired level
    ; Example: Turn off both LEDs
    BCF     COOLER, 0 ; Clear PORTD,1 (Cooling LED)
    BCF     HEATER, 0 ; Clear PORTD,2 (Heater LED)
    GOTO    START

	
