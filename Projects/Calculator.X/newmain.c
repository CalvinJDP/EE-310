/*
 * ---------------------
 * Title: Calculator
 * ---------------------
 * Program Details:
 *  Takes two integers and performs calculating output is in binary
 * Inputs: a, b 
 * Outputs: s
 * Setup: C- Simulator
 * Date: Apr 9, 2024
 * File Dependencies / Libraries: It is required to include the 
 * Configuration Header File 
 * Compiler: xc8, 6.2
 * Author: Calvin Pereira
 * Versions:
 *      V1.0: Original
*/

// PIC18F46K42 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config FEXTOSC = LP     // External Oscillator Selection (LP (crystal oscillator) optimized for 32.768 kHz; PFM set to low power)
#pragma config RSTOSC = EXTOSC  // Reset Oscillator Selection (EXTOSC operating per FEXTOSC bits (device manufacturing default))


// CONFIG1H
#pragma config CLKOUTEN = OFF   // Clock out Enable bit (CLKOUT function is disabled)
#pragma config PR1WAY = ON      // PRLOCKED One-Way Set Enable bit (PRLOCK bit can be cleared and set only once)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)

// CONFIG2L
#pragma config MCLRE = EXTMCLR  // MCLR Enable bit (If LVP = 0, MCLR pin is MCLR; If LVP = 1, RE3 pin function is MCLR )
#pragma config PWRTS = PWRT_OFF // Power-up timer selection bits (PWRT is disabled)
#pragma config MVECEN = ON      // Multi-vector enable bit (Multi-vector enabled, Vector table used for interrupts)
#pragma config IVT1WAY = ON     // IVTLOCK bit One-way set enable bit (IVTLOCK bit can be cleared and set only once)
#pragma config LPBOREN = OFF    // Low Power BOR Enable bit (ULPBOR disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled , SBOREN bit is ignored)

// CONFIG2H
#pragma config BORV = VBOR_2P45 // Brown-out Reset Voltage Selection bits (Brown-out Reset Voltage (VBOR) set to 2.45V)
#pragma config ZCD = OFF        // ZCD Disable bit (ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config PPS1WAY = ON     // PPSLOCK bit One-Way Set Enable bit (PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle)
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config DEBUG = OFF      // Debugger Enable bit (Background debugger disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Extended Instruction Set and Indexed Addressing Mode disabled)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period selection bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled; SWDTEN is ignored)

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4L
#pragma config BBSIZE = BBSIZE_512// Boot Block Size selection bits (Boot Block size is 512 words)
#pragma config BBEN = OFF       // Boot Block enable bit (Boot block disabled)
#pragma config SAFEN = OFF      // Storage Area Flash enable bit (SAF disabled)
#pragma config WRTAPP = OFF     // Application Block write protection bit (Application Block not write protected)

// CONFIG4H
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block not write-protected)
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)
#pragma config WRTSAF = OFF     // SAF Write protection bit (SAF not Write Protected)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored)

// CONFIG5L
#pragma config CP = OFF         // PFM and Data EEPROM Code Protection bit (PFM and Data EEPROM code protection disabled)

#include <xc.h> // must have this


//#include "../../../../../Program Files/Microchip/xc8/v2.40/pic/include/proc/pic18f46k42.h"
#include "C:\Program Files\Microchip\xc8\v2.46\pic\include\proc\pic18f46k42.h"
//#include "C:\Program Files\Microchip\xc8\v2.40\pic\include\proc\pic18f46k42"

#define _XTAL_FREQ 4000000                 // Fosc  frequency for _delay()  library
#define FCY    _XTAL_FREQ/4


int a = -1; //Fisrt Integer
int b = -1; //Second Integer
int c = -1; //Multiplier
int s = -1; //Sum

int buttonPress() {
    PORTCbits.RC7 = 0;
    PORTCbits.RC7 = 1;
    if (PORTAbits.RA3 == 1) {
        return 1;
        
    }
    if (PORTAbits.RA2 == 1) {
        return 2;
    }  
    
    if (PORTAbits.RA1 == 1) {
        return 3;
    }
    
    if (PORTAbits.RA0 == 1) {
        return 10;
    }
    PORTCbits.RC7 = 0;
    
    
    
    PORTAbits.RA6 = 1;
    if (PORTAbits.RA3 == 1) {
        return 4;
    }
    if (PORTAbits.RA2 == 1) {
        return 5;
    }  
    
    if (PORTAbits.RA1 == 1) {
        return 6;
    }
    
    if (PORTAbits.RA0 == 1) {
        return 11;
    }
    PORTAbits.RA6 = 0;
    
    
    
    
    
    
    
    PORTAbits.RA5 = 1;
    if (PORTAbits.RA3 == 1) {
        return 7;
    }
    if (PORTAbits.RA2 == 1) {
        return 8;
    }  
    
    if (PORTAbits.RA1 == 1) {
        return 9;
    }
    
    if (PORTAbits.RA0 == 1) {
        return 12;
    }
    PORTAbits.RA5 = 0;
    
    
    
    
    
    
    PORTAbits.RA4 = 1;
    if (PORTAbits.RA3 == 1) {
        return 20;
    }
    if (PORTAbits.RA2 == 1) {
        return 0;
    }  
    
    if (PORTAbits.RA1 == 1) {
        return 21;
    }
    
    if (PORTAbits.RA0 == 1) {
        return 13;
    }
    PORTAbits.RA4 = 0;
    
    return -1;

}

void CalcOut(void) {
    
}

int CCCC() {
    while (c == -1) {
        c = buttonPress();
    }
    if (c > 9 && c < 20) {
        
        return 1;
    }
    else {
        c = -1;
        return 0;
        
    }
}

int AAAA() {
    while (a == -1) {
        a = buttonPress();
    }
    if (a >= 0 && a <= 9) {
        PORTD = 0; 
        PORTDbits.RD0 = 1;
        return 1;
    }
    else {
        a = -1;
        return 0;
    }
}

int BBBB() {
    // Call function button press
    while (b == -1) {
        b = buttonPress();
    }
    
    // If button is valid return 1  
    if (b >= 0 && b <= 9) {
        PORTD = 0; 
        PORTDbits.RD1 = 1;
        return 1;
    }
    else {
        b = -1;
        return 0;
    }
}

void main(void) {
    PORTA= 0;
    LATA = 0;
    ANSELA = 0;
    TRISA = 0b00001111;
    
    PORTD= 0;
    LATD = 0;
    ANSELD = 0;
    TRISD = 0b00000000;
    
    PORTC= 0;
    LATC = 0;
    ANSELC = 0;
    TRISC = 0b00000000;
    
    // Define variables
    c = -1; // Operand
    a = -1; // First integer
    b = -1; // Second integer
    int sharp = -1; // Check for sharp button press
    
    while (1) {
       
        // functions used to read button press if buttons are valid returns 1
        if ( AAAA() == 1 && CCCC() == 1 && BBBB() == 1) {
            switch(c) {
                case 10:
                    s = a + b;
                    
                    break;
               case 11:
                   s = a - b;
                    
                    break;
                case 12:
                    s = a * b;
                    break;
                case 13:
                    s = a/b;
                }
        }
        
        // After operation is complete output to leds                                                                                                                       
        while (sharp == -1) {
            sharp = buttonPress();
            if (sharp == 21) {
                PORTD = 0;
                
                PORTD = (unsigned char)(s & 0xFF);
                __delay_ms(5);
                
                c = -1;
                a = -1;
                b = -1;       
                sharp = -1;
                PORTD = 0;
                break;
            }
            else {
                sharp = -1;
            }
            if (sharp == 20) {
                
            }
        }
    
    }
    return;
}





