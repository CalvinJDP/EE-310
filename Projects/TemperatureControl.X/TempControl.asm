//-----------------------------
// Title: Temperature Control
//-----------------------------
// Purpose: what does this program do? 
// Dependencies: AssemblyConfig.inc
// Compiler: MPLAB X IDE v6.20
// Author: Calvin Pereira
// OUTPUTS: Outputs to two LEDS PORTD1 and PORTD2
//	    PORTD1 - Signifies cooling fan
//	    PORTD2 - Signifies hot air blower
// INPUTS: User will input their desired temperature through a keypad
// Versions:
//  	V1.0: today?s date - First version 
//  	
//-----------------------------


    
#----------------
# PROGRAM INPUTS
#----------------
#define  measuredTempInput 	45 ; this is the input value
#define  refTempInput 		25 ; this is the input value

#----------------
# REGISTERS
#----------------
#define  measuredTempREG 	0x20 ; this is
#define  refTempREG 		0x21 ; this is 



#----------------
# PROGRAM OUTPUTS
#----------------
#define	  measuredTempDecimal 	0x70 ; this is the input value
#define	  refTempInputDecima     ; this is the input value
#define   HEATER      PORTD,2
#define   COOLER  PORTD,1
