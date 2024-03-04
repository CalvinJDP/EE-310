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

    
    
;----------------
; PROGRAM INPUTS
;----------------
#define	    measuredTempInput 	45d	; Input for measured from sensor
#define	    refTempInput	25d	; Input from user

;----------------
; REGISTERS
;----------------
#define	    measuredTempREG 	0x20	; Setting reg 20 to store measured temp
#define	    refTempREG 		0x21	; Setting reg 21 to store reference temp



;----------------
; PROGRAM OUTPUTS
;----------------
#define	    DCrefTempA		0x60	; Used to store decimal value of Refernece Temp
#define	    DCrefTempB		0x61	; Used to store decimal value of Refernece Temp
#define	    DCrefTempC		0x62	; Used to store decimal value of Refernece Temp
    
#define	    DCmesTempA		0x70	; Used to store decimal value of Measured Temp
#define	    DCmesTempB		0x71	; Used to store decimal value of Measured Temp
#define	    DCmesTempC		0x72	; Used to store decimal value of Measured Temp
    
#define	    HEATER    PORTD,2		; Sets PORTD 2 to the heater LED
#define	    COOLER    PORTD,1		; Sets PORTD 1 to the coller LED

    
    If measuredTemp=refTemp then
	set contReg = 0
	GOTO LED_OFF

    If measuredTemp>refTemp then
	set contReg = 2
	GOTO LED_HOT
	
    else
	set contReg = 1
	GOTO LED_COOL
	
LED_HOT:
	

	
LED_COOl:
	
		
LED_OFF: 
	
	
