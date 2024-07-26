.include "m32def.inc" 

.equ number = 0x3F 
   
.org 0
  
ldi R16, 0xFF ; Set all PORTC pins as outputs
out DDRC, R16 
cbi DDRA, 0 ; Set PORTA0 as input (button pin)

; Initialize 'number' variable to zero
ldi R16, 0x3F
sts number, R16
lds R16, number
out PORTC, R16
MAIN_LOOP:

  sbis PINA, 0 ; Check if the button is pressed
  rjmp BUTTON_PRESS

  cpi R16, 0x6D ; Check if the displayed number is 9
  breq TURN_OFF_LEDS



  rjmp MAIN_LOOP
TURN_OFF_LEDS:
    
    ldi R16, 0xFF ; Turn on all LEDs on the seven-segment display
    out PORTC, R16
    ldi R16, 100
    CALL DELAY

    ; Turn off LEDs one by one
    ldi R16, 0x6F
    TURN_OFF_LOOP:
        CALL DELAY
        dec R16
        brne TURN_OFF_LOOP  ; Continue turning off LEDs until R16 reaches 0x3F
    cpi R16, 0x3F
	rjmp MAIN_LOOP

BUTTON_PRESS:
  
  ; Increment the number displayed (stored in R16)
  inc R16
  out PORTC,R16
  rjmp MAIN_LOOP
DELAY:
    
	; Generate a delay of 100 microseconds using a loop that decrements a counter
    ldi R16, 100
    DELAY_LOOP:
        nop
        dec R16
        brne DELAY_LOOP

    ret ; Return to the calling instruction
