#include "./newAsmTemplate.inc"
#include <xc.inc>


Counter	    EQU	    20h
SegDisplay  EQU     LATD   
LimitH	    EQU	    21h
LimitL	    EQU	    22h
ZeroRange    EQU    23h
DCounter    EQU	    24h
InnerLoopCount EQU  25h
OuterLoopCount EQU  26h
OutermostLoopCount  EQU	27h
FSR EQU 0x04 
    


#define	    ButtonA	PORTB, 0
#define	    ButtonB	PORTB, 1
    
  
  
  
    PSECT absdata,abs,ovrld
    ORG 0h
    
    ORG 0x1FF0
    
    DB 0b00111111 ; 0
    DB 0b00000110 ; 1
    DB 0b01011011 ; 2
    DB 0b01001111 ; 3
    DB 0b01100110 ; 4
    DB 0b01101101 ; 5
    DB 0b01111101 ; 6
    DB 0b00000111 ; 7
    DB 0b01111111 ; 8
    DB 0b01100111 ; 9
    DB 0b01110111 ; A
    DB 0b01111111 ; B
    DB 0b00111001 ; C
    DB 0b00111111 ; D
    DB 0b01111001 ; E
    DB 0b01110001 ; F
  
    ORG 0020h
    GOTO setup
    
setup:
    CLRF WREG
    MOVLW 0x10
    MOVWF LimitH
    MOVLW 0x00
    MOVWF LimitL
    MOVLW 0xFF
    MOVWF ZeroRange
    CLRF WREG
    BANKSEL	PORTB 
    CLRF	PORTB 
    BANKSEL	LATB 
    CLRF	LATB 
    BANKSEL	ANSELB 
    CLRF	ANSELB 
    BANKSEL	TRISB 
    MOVLW	0b11111111 
    MOVWF	TRISB 
    BANKSEL    LATD 
    CLRF    LATD 
    BANKSEL    TRISD 
    CLRF    TRISD 
    GOTO Loop
   

    
Loop:
    ; Check Button A
    BTFSC ButtonA 
    GOTO CheckBothButtons 
    
    ; Check Button B
    BTFSC ButtonB 
    GOTO CheckBothButtonsB 

    
    

    RCALL UpdateDisplay 
    RCALL Delay
    GOTO Loop 



CheckBothButtons:
    BTFSC ButtonB
    GOTO ResetCounter
    GOTO IncCounter
    GOTO Loop

CheckBothButtonsB:
    BTFSC ButtonA
    GOTO ResetCounter
    GOTO DecCounter
    GOTO Loop

Delay:
    MOVLW 0x05 
    MOVWF OutermostLoopCount 

OutermostLoop:

    MOVLW 0xFF 
    MOVWF OuterLoopCount 

OuterLoop:

    MOVLW 0xFF

    MOVWF InnerLoopCount 

InnerLoop:

    DECFSZ InnerLoopCount, F
    GOTO InnerLoop
    DECFSZ OuterLoopCount, F
    GOTO OuterLoop
    DECFSZ OutermostLoopCount, F
    GOTO OutermostLoop
    RETURN
    
    
IncCounter:
    INCF Counter, F 
    GOTO CheckLimits 
    Return
    
DecCounter:
    DECF Counter, F 
    MOVFF Counter, WREG
    CPFSEQ ZeroRange
    GOTO CheckLimits 
    RCALL ZeroCount
    NOP
    Return
    
ZeroCount:
    MOVLW 0x0F
    MOVWF Counter
    GOTO UpdateDisplay
    RETURN
    
CheckLimits:
    
    MOVF Counter, W
    CPFSGT LimitH 
    CALL WrapAround 
    GOTO UpdateDisplay 
    ; Check if counter is zero
    CPFSEQ LimitL 
    GOTO UpdateDisplay
    ; Counter is less than zero
    GOTO ResetCounterB 

    RETURN

WrapAround:
    MOVLW 0x00
    MOVWF Counter
    RETURN
    
ResetCounter:
    MOVLW 0x00
    MOVWF Counter 
    GOTO UpdateDisplay 
    RETURN
 
ResetCounterB:
    RCALL UpdateDisplayB
    MOVLW 0x0F
    MOVWF Counter
    GOTO UpdateDisplay
    RETURN
    
UpdateDisplay:
    RCALL Delay
    MOVFF Counter, WREG
    ADDLW 0xF0
    MOVWF TBLPTRL
    MOVLW 0x1F
    MOVWF TBLPTRH
    MOVLW 0x0
    MOVWF TBLPTRU
    TBLRD*
    MOVFF TABLAT, WREG
    MOVFF WREG, PORTD
    GOTO Loop
    
UpdateDisplayB:
    MOVFF Counter, WREG
    ADDLW 0xF0
    MOVWF TBLPTRL
    MOVLW 0x1F
    MOVWF TBLPTRH
    MOVLW 0x0
    MOVWF TBLPTRU
    TBLRD*
    MOVFF TABLAT, WREG
    MOVFF WREG, PORTD
    RETURN





    

