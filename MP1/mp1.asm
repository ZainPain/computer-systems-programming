; This program that I've created is an example of a Stack Calculator in LC3.
; It features only basic operations such as '+' (add), '-' (minus),
; '*' (multiplication), '/' (division), and '^' (exponents). It supports single
; digit operations and uses a stack to maintain data values.
; the result will be displayed in hexadecimal notation or one can view Register
; 6 which will also contain the result in Hexadecimal notation.
; Some challenges encountered included struggling to get the logic for the
; operators correct, and figuring out the proper control logic to branch to the
; correct operators. 
;
; Assuming user will only enter ' ' 0-9 *+/-
 
.ORIG x3000
 
    AND R0, R0, #0          ; zero out all registers
    AND R6, R6, #0
    AND R4, R4, #0
    AND R1, R1, #0
    AND R2, R2, #0
    AND R3, R3, #0
    AND R5, R5, #0
 
GET_NEXT_CHAR
    GETC                ; get character from user input
    OUT                                 ; push character to screen
    ADD R3, R0, #0      ; negate this character and store in R3
    NOT R3, R3
    ADD R3, R3, #1
    LD R1, NEW_LINE             ; check if char is /n
    ADD R5, R1, R3
    BRz DONE            ; if '/n' branch to done
    LD R1, CHAR_RETURN  ; check if char is /r
    ADD R5, R1, R3
    BRz DONE            ; if '/r' branch to done
    LD  R1, SPACE       ; check if space
    ADD R5, R1, R3
    BRz GET_NEXT_CHAR   ; if space, get the next char and ignore
    JSR EVALUATE                ; if none of these, it is operand/operator/invalid
 
    BRnzp GET_NEXT_CHAR ; after evaluating, get the next char
DE_ERR
    LD R0, INPUT_ERROR  ; print an input error when invalid input is provided
    PUTS
 
DONE    JSR POP                 ; check for errors in execution before halting
    JSR POP
    ADD R5, R5, #0
    BRz EXP_ERR                 ; if error detected, print error
    JSR PRINT_HEX       ; print character in hexadecimal to screen
EXP_ERR LEA R0, EXP_ERR_MSG     ; if invalid expression, print that to screen
    PUTS
    AND R6, R6, #0
    HALT
 
SPACE   .FILL x0020
NEW_LINE    .FILL x000A
CHAR_RETURN .FILL x000D
EXP_ERR_MSG .STRINGZ "\nInvalid Expression"
INPUT_ERROR .STRINGZ "\nInvalid Input"
 
 
; R6- value to print in hexadecimal
PRINT_HEX ;;This subroutine was added in the second checkpoint to print the hexadecimal value of the answer to the computations
    AND R0, R0, #0 		;;All the registers must be cleared first 
    AND R4, R4, #0 		;;All the registers must be cleared first 
    ADD R4, R6, #0 		;;All the registers must be cleared first 
    AND R5, R5, #0 		;;All the registers must be cleared first 
    ADD R5, R5, #4 		;;A hex value is composed of 4 digits, in order to increment through them, we must set R5 to 4 initially.
LOOP_TOP ;;The outerloop
    ADD R5, R5, #0      	;;This is a dummy line so that the BRz affects the value in R5
    BRz DONE_PRINTING   	;;Once the counter of R5 goes to 0, we know we are done printing
 
    AND R3, R3, #0      	;;Clear R3
    ADD R3, R3, #4      	;;Set the bits within each hex counter to 4
    ADD R5, R5, #-1     	;;Decrement R5 upon completion of one of the hex values
LOOP_INNER              	;;another loop inside the LOOP_TOP
    ADD R3, R3, #0      	;;Dummy to branch using the value in R3
    BRz PRINT_DIGIT     	;;When R3 is 0, print
    ADD R0, R0, R0      	;;Add R0 by itself
 
    ADD R4, R4, #0
    BRn ADD_ONE         	;;This simply follows what is given in the sample flowchart
    BRzp ADD_ZERO       	;;Follows the sample flowchart
       
ADD_ONE                	 	;;We take the value of R0 and add one
    ADD R0, R0, #1
 
    BRnzp SHIFT_LEFT
ADD_ZERO               
   
    BRnzp SHIFT_LEFT
SHIFT_LEFT
    ADD R4, R4, R4
 
    ADD R3, R3, #-1
    BRnzp LOOP_INNER
 
PRINT_DIGIT             	;;The act of printing the digit
    AND R2, R2, #0
    LD R2, DIGIT_NINE
    NOT R2, R2			;;subtracting 9 from R0
    ADD R2, R2, #1
 
    ADD R2, R2, R0
    BRn ADD_ZERO_PRINT
    BRzp ADD_OTHER_PRINT
 
ADD_ZERO_PRINT		
    AND R1, R1, #0
    LD R1, DIGIT_ZERO
    ADD R0, R0, R1
    BRnzp ACTUAL_PRINT
 
ADD_OTHER_PRINT
    AND R1, R1, #0
    LD R1, DIGIT_OTHER
    ADD R0, R0, R1
    BRnzp ACTUAL_PRINT
 
ACTUAL_PRINT
    OUT				;;displays result in Hex
    AND R0, R0, #0
    BRnzp LOOP_TOP
 
DONE_PRINTING			;;Finally finished
    HALT
 
DIGIT_NINE  .FILL   x0009
DIGIT_ZERO  .FILL   x0030
DIGIT_OTHER .FILL   x0037
 
; R0 - character input from keyboard
; R6 - current numerical output
;
; Determines what the correct place to jump to is
; (either if it is an operand, or operator)
EVALUATE
    ST R1, EVALUATE_R1      ; callee-saved reg
    ST R2, EVALUATE_R2          ; callee-saved reg
    ST R3, EVALUATE_R3          ; callee-saved reg
    ST R5, EVALUATE_R5      ; callee-saved reg
    ST R7, EVALUATE_R7          ; callee-saved reg
    LD R1, NINE                         ; check if value is above ASCII '9'
    NOT R1, R1
    ADD R1, R1, #1
    ADD R5, R0, R1
    BRp EXPO                            ; if above ASCII '9', it must be exponent
    LD R1,  ZERO                        ; check if below ASCII '0'
    NOT R1, R1
    ADD R1, R1, #1
    ADD R5, R0, R1
    BRn OPERATOR                        ; if below ASCII '0', it is one of +-*/
    ADD R0, R5, #0          ; if number, move that number to R0 and PUSH
    JSR PUSH
    LD R1, EVALUATE_R1      ; callee-saved reg
    LD R2, EVALUATE_R2          ; callee-saved reg
    LD R3, EVALUATE_R3          ; callee-saved reg
    LD R5, EVALUATE_R5      ; callee-saved reg
    LD R7, EVALUATE_R7          ; callee-saved reg
    BRnzp GET_NEXT_CHAR     ; get the next character
OPERATOR
    NOT R0, R0
    ADD R0, R0, #1
    LD R1, OP_ADD                       ; check if add operation
    ADD R5, R1, R0
    BRz PLUS_OP                         ; if add, branch to plus operator
    LD R1, OP_MIN                       ; check if minus operation
    ADD R5, R1, R0
    BRz MIN_OP                          ; if minus, branch to minus operator
    LD R1, OP_MUL                       ; check if multiply operator
    ADD R5, R1, R0
    BRz MUL_OP                          ; if multiply, branch to multiply operator
    LD R1, OP_DIV                       ; check if divide operator
    ADD R5, R1, R0
    BRz DIV_OP                          ; if divide, branch to divide operator
    BRnzp DE_ERR                        ; if none of these, it is invalid input, so print that
EXPO    LD R1, OP_EXP           ; handle the exponent case called from abov
    NOT R0, R0
    ADD R0, R0, #1
    ADD R5, R1, R0
    BRz EXP_OP                  ; branch if indeed exponent
 
 
NINE    .FILL x0039
ZERO    .FILL x0030
OP_ADD  .FILL x002B
OP_MIN  .FILL x002D
OP_MUL  .FILL x002A
OP_DIV  .FILL x002F
OP_EXP  .FILL x005E
EVALUATE_R1 .FILL x43D4
EVALUATE_R2 .FILL x43D5
EVALUATE_R3 .FILL x0000
EVALUATE_R5 .FILL x43D7
EVALUATE_R7 .FILL x43D8
 
 
;input R3, R4
;out R0
PLUS_OP
; Add the two topmost values on the stack using the ADD command and store the result
; into R6 and R0
    JSR POP
    ADD R3, R0, #0
    JSR POP
    ADD R4, R0, #0
    ADD R0, R3, R4 ;;Adds the values of R3 and R4 and stores it in R0
    ADD R6, R0, #0
    JSR PUSH
    BRnzp GET_NEXT_CHAR
 
;input R3, R4
;out R0
MIN_OP
; Subtract the two topmost values on the stack by negating one and adding the two,
; and store the result into R6 and R0
    JSR POP
    ADD R3, R0, #0
    JSR POP
    ADD R4, R0, #0
    NOT R3, R3
    ADD R3, R3, #1
    ADD R0, R3, R4
    ADD R6, R0, #0
    JSR PUSH
    BRnzp GET_NEXT_CHAR
 
 
;input R3, R4
;out R0
MUL_OP
; Multiply the two topmost values on the stack by adding one number to itself, the
; other number's times, and store the result into R6 and R0
    JSR POP
    ADD R3, R0, #0
    JSR POP
    ADD R4, R0, #0
 
    AND R0, R0, #0
MULLOOP ADD R0, R3, R0
    ADD R4, R4, #-1
    BRnp MULLOOP
    ADD R6, R0, #0
    JSR PUSH
    BRnzp GET_NEXT_CHAR
 
 
;input R3, R4
;out R0
DIV_OP
; Divide the two topmost values on the stack by repeatedly substracting one value from
; another and incrementing the counter, and store the counter into R6 and R0
    JSR POP
    ADD R3, R0, #0
    JSR POP
    ADD R4, R0, #0
 
    NOT R3, R3
    ADD R3, R3, #1
    AND R0, R0, #0
DIVLOOP ADD R0, R0, #1
    ADD R4, R3, R4
    BRzp DIVLOOP
    ADD R0, R0, #-1
    ADD R6, R0, #0
    JSR PUSH
    BRnzp GET_NEXT_CHAR
 
 
;input R3, R4
;out R0
EXP_OP
; Compute the exponent by having two multiply loops nested and store the result in R6
    JSR POP
    ADD R4, R0, #0
    JSR POP
    ADD R3, R0, #0
 
    AND R0, R0, #0
    AND R5, R5, #0
    ADD R5, R4, #0
    AND R4, R4, #0
    ADD R4, R3, #0
    ADD R5, R5, #-1
    AND R1, R1, #0
    ADD R1, R3, #0 ;; R1 holds base value
EXP_OUTER_LOOP
    ADD R0, R0, #0
    ADD R4, R1, #0  ;; Reload base value
 
EXP_INNER_LOOP
    ADD R0, R3, R0
    ADD R4, R4, #-1
    BRp EXP_INNER_LOOP
    AND R3, R3, #0
    ADD R3, R0, #0
    AND R0, R0, #0
    ADD R5, R5, #-1
    BRp EXP_OUTER_LOOP
    ADD R6, R3, #0
    JSR PUSH
    BRnzp GET_NEXT_CHAR
 
 
; Stack implemented in LC3
; IN:R0, OUT:R5 (0-success, 1-fail/overflow)
; R3: STACK_END R4: STACK_TOP
PUSH
    ST R3, PUSH_SaveR3  ; save R3
    ST R4, PUSH_SaveR4  ; save R4
    AND R5, R5, #0
    LD R3, STACK_END
    LD R4, STACk_TOP
    ADD R3, R3, #-1
    NOT R3, R3
    ADD R3, R3, #1
    ADD R3, R3, R4
    BRz OVERFLOW        ; stack is full
    STR R0, R4, #0      ; no overflow, store value in the stack
    ADD R4, R4, #-1     ; move top of the stack
    ST R4, STACK_TOP    ; store top of stack pointer
    BRnzp DONE_PUSH
OVERFLOW
    ADD R5, R5, #1
DONE_PUSH
    LD R3, PUSH_SaveR3  ; load back the saved R3
    LD R4, PUSH_SaveR4  ; load back the saved R4
    RET
 
 
PUSH_SaveR3 .BLKW #1
PUSH_SaveR4 .BLKW #1
 
 
; OUT: R0, OUT R5 (0-success, 1-fail/underflow)
; R3 STACK_START R4 STACK_TOP
POP
    ST R3, POP_SaveR3   ; save R3
    ST R4, POP_SaveR4   ; save R3
    AND R5, R5, #0      ; clear R5
    LD R3, STACK_START
    LD R4, STACK_TOP
    NOT R3, R3
    ADD R3, R3, #1
    ADD R3, R3, R4
    BRz UNDERFLOW
    ADD R4, R4, #1
    LDR R0, R4, #0
    ST R4, STACK_TOP
    BRnzp DONE_POP
UNDERFLOW
    ADD R5, R5, #1
DONE_POP
    LD R3, POP_SaveR3   ; load back the saved R3 value
    LD R4, POP_SaveR4   ; load back the saved R4 value
    RET
 
POP_SaveR3  .BLKW #1
POP_SaveR4  .BLKW #1
STACK_END   .FILL x3FF0
STACK_START .FILL x4000
STACK_TOP   .FILL x4000
 
.END
