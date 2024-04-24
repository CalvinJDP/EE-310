/*
 * The purpose of this program is demonstrate INT01 as an external interrupt.
 * In this case when the signal changes state on RB0(INT01) then D0 starts
 * blinking for 4 seconds and then stops. The results can be simulated and
 * verified.
 *
 * Author: Farid Farahmand
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
//#include "C:\Program Files\Microchip\xc8\v2.40\pic\include\proc\pic18f46k42"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define _XTAL_FREQ 4000000                 // Fosc  frequency for _delay()  library
#define FCY    _XTAL_FREQ/4

#define Vref 5.0 // voltage reference 

const uint8_t segmentPatterns[10] = {
    //    a  b  c  d  e  f  g (segment)
    // g f a b dp c d e
    
    0b11010111,  // 0
    0b01000100,  // 1
    0b11100011,  // 2
    0b11100110,  // 3
    0b11010100,  // 4
    0b11100110,  // 5
    0b11100111,  // 6
    0b00110100,  // 7
    0b11110111,  // 8
    0b11110110,  // 9
    // Add patterns for binary 10, 11, 12, 13, 14, 15 if needed
};


int digital; // holds the digital value 
float voltage; // hold the analog value (volt))
char data[10];
void setupPorts(void);
int conv();
void scanKeypad(void);
void error();
int countA = 0;
int countB = 0;
int prA = 0;
int prB = 0;
int vSwitch = 0;
int HCode = 2;
int LCode = 3;
int pressedKey = -1;
int temp = 0;

/*This code block configures the ADC
for polling, VDD and VSS references, ADCRC
oscillator and AN0 input.
Conversion start & polling for completion
are included.
 */
void main() {
    //ADC Initialization
    setupPorts();
    uint8_t pattern = segmentPatterns[0];
    while (1) {
        ADPCH = 0x03;
        prA = conv();
        ADPCH = 0x04;
        prB = conv();
        
        scanKeypad();
        
        if (pressedKey == 10) {
            temp = 1;
            HCode = -1;
            LCode = -1;
            PORTCbits.RC3 = 0;
            __delay_ms(500);
            PORTCbits.RC3 = 1;
            
            while (temp == 1) {
                scanKeypad();
                if (pressedKey > -1) {
                    pressedKey = HCode;
                    uint8_t pattern = segmentPatterns[HCode]; 
                    PORTD = pattern;
                    __delay_ms(500);
                    PORTD = 0x00;
                    
                    
                }
                if (HCode > -1 && pressedKey > -1) {
                    pressedKey = LCode;
                    uint8_t pattern = segmentPatterns[LCode]; 
                    PORTD = pattern;
                    __delay_ms(500);
                    PORTD = 0x00;
                    temp = 0;
                }
            }
        }
        else {
            pressedKey = -1;
        }
        
        if (PORTCbits.RC4 == 1) {
            vSwitch = 1;
        }
        else {
            vSwitch = 0;
        }
        
        
        if (prA == 1) {
            ++countA;
            if (countA >= 1) {
            uint8_t pattern = segmentPatterns[countA];    
            // Display the pattern here
            PORTD = pattern;
            
            }
        }
        if (prB == 1) {
            ++countB;
            if (countB >= 1) {
                uint8_t pattern = segmentPatterns[countB];
                PORTD = pattern;
            }
        }
        
        
        //PORTD = pattern;
        __delay_ms(500);
        
        if (countA > 3 || countB > 3) {
            error();
        }
         
        if (countA == HCode && countB == LCode  && vSwitch == 1) {
            PORTCbits.RC5 = 1;
            __delay_ms(2000);
            PORTCbits.RC5 = 0;
            countA = 0;
            countB = 0;
            
        }
        if (vSwitch == 1 && countA != HCode && countB != LCode) {
            error();
        }
        
        
        
    }
}

void error() {
    PORTD = segmentPatterns[0];
    for (int i = 0; i < 4; ++i) {
        PORTC = 0x08;
        __delay_ms(500);
        PORTC = 0x00;
        __delay_ms(500);
            }
    countA = 0;
    countB = 0;
}

int conv() {
    ADCON0bits.GO = 1; //Start conversion
    while (ADCON0bits.GO); //Wait for conversion done
    digital = (ADRESH*256) | (ADRESL);/*Combine 8-bit LSB and 2-bit MSB*/
    voltage= digital*((float)Vref/(float)(4096));
    
    if (voltage > 0.200) {
        return 0;
    }
    else if (voltage > 3) {
        return 1;
    }
    else {
        return 1;
    }
    
}

void setupPorts(void)
{
       //Setup ADC
    
    TRISD = 0x00;
    ANSELD = 0x00;
    PORTD = 0x00;
    
    TRISC = 0b00010000;
    ANSELC = 0x00;
    PORTC = 0x0C;
    
    TRISA = 0x03;
    
    TRISB = 0x0F;
    ANSELB = 0x00;
    PORTB = 0x00;
    
    PORTCbits.RC5 = 0; 
    
    
    ADCON0bits.FM = 1;  //right justify
    ADCON0bits.CS = 1; //ADCRC Clock
    
    TRISAbits.TRISA3 = 1;
    TRISAbits.TRISA4 = 1;
    TRISAbits.TRISA5 = 1;
    
    ANSELAbits.ANSELA3 = 1;
    ANSELAbits.ANSELA4 = 1;
    ANSELAbits.ANSELA5 = 1;
    // Added 
    ADPCH = 0x03; //Set RA0 as Analog channel in ADC ADPCH
    ADCLK = 0x00; //set ADC CLOCK Selection register to zero
    
    ADRESH = 0x00; // Clear ADC Result registers
    ADRESL = 0x00; 
    
    ADPREL = 0x00; // set precharge select to 0 in register ADPERL & ADPERH
    ADPREH = 0x00; 
    
    ADACQL = 0x00;  // set acquisition low and high byte to zero 
    ADACQH = 0x00;    
    
    ADCON0bits.ON = 1; //Turn ADC On 
}


void scanKeypad(void) {
    const int keypadLayout[4][3] = {
        {1, 2, 3}, // Row 0, Column 0-2
        {4, 5, 6}, // Row 1, Column 0-2
        {7, 8, 9}, // Row 2, Column 0-2
        {10, 0, 11}  // Row 3, Column 0-2
    };

    // Setup Ports
    TRISB = 0x07; // RB0-RB2 as inputs, RB3-RB5 as outputs
    TRISA = 0x0F; // RA0-RA3 as inputs
    PORTB = 0x00; // Initialize port B to 0

    // Scan columns (RB3-RB5)
    for (int col = 0; col < 3; col++) {
        PORTB = (0b00001000 << col); // Activate one column at a time
        __delay_ms(5); // Wait for signals to stabilize

        // Check rows (RB0-RB2) for pressed keys
        for (int row = 0; row < 4; row++) {
            if (PORTBbits.RB0 == 0 && PORTBbits.RB1 == 0 && PORTBbits.RB2 == 0) {
                // No keys pressed in this column
                continue;
            }

            // Key pressed, decode the key
            int pressedKey = keypadLayout[row][col];
            // Convert the pressedKey to an integer and return
            
        }
    }

    // No key pressed
    
}