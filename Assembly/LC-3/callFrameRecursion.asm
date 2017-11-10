;Register Usage;
;R0   Pass to/from StackBase
;R5   Frame pointer
;R6   Stack pointer

;      Doesn't work atm

; Find square of number through **Recursion**
;   square(n) = square(n - 1) + 2n - 1 for n > 0
;     and
;   square(0) = 0
;    Now will pass just one variable (n)

; ***Can just click on the file name in the bottom left and it will copy the address of the file
; ** Control + V will paste into the LC-3 program, not cmd + v

          .ORIG x3000
          LD   R6, StackBase    ; R6 now contains the address of the Stack
          AND  R5, R5, #0       ; The main method does not need a frame pointer

          ; push parameter(n) onto stack
          LDI  R0, pN
          JSR  Push

          ; Call our function to perform computation
          JSR  Simple

          ; Get return value then...
          JSR  Pop

          ; Storing value (R0) - value stored into location at pResult
          STI  R0, pResult

          ; clean up stack frame by removing parameter
          JSR  Pop
          HALT



Push      ADD  R6, R6, #-1
          STR R0, R6, #0
          RET

Pop       LDR R0, R6, #0
          ADD R6, R6, #1
          RET

; Do recursion by actually calling BRp Simple and not looping within??
;    -yes
Simple    ADD  R0, R7, #0
          JSR Push
          JSR Push

          ADD R0, R5, #0
          JSR Push

          ADD R5, R6, #-1

          ADD R0, R1, #0
          JSR Push

          ; computation starts here
          LDR R4, R5, #4  ; to get N value - put in R4
          AND R3, R3, #0  ;  Clear R3 - act as accumulator
          AND R2, R2, #0  ;  Clear R2 - act as counter

          ; start of loop to check value - set cc
check0    ADD R2, R2, #0
          ; check if 0 - if yes, jump below
          BRnz FinishComp

          ; if not 0
          ; do computation, store in R4
          ADD R4, R2, #0  ; put R2 value into R4
          ADD R4, R4, R4  ;  2n
          ADD R4, R4, #-1 ;  2n - 1
          ADD R3, R3, R4  ; now put this into R0 to store it iteration value

          ;ADD R4, R4, #1  ; R4 back to 2n
          ;AND R2, R2, #0  ; clear R2
          ;ADD R2, R4, #0  ; add R4 to R2
          ;NOT R2, R2      ; flip bits, add 1
          ;ADD R2, R2, #1  ; R2 is now negation of R4 (-2n)

          ADD R2, R2, #-1 ; decrement n
          BRnzp check0    ; back to top


          ; clean up and return
          ; *** PUT value back into R0 before returning
FinishComp     ADD R0, R3, #0  ; add acumulated value to R0
               ADD R1, R5, #3
               STR R0, R1, #0  ; put R0 into R1

          JSR Pop
          ADD R1, R0, #0

          ; Fetch and restore the frame pointer
          JSR Pop
          ADD R5, R0, #0

          ; Fetch and restore the return address
          JSR Pop
          ADD R7, R0, #0
          RET


StackBase .FILL x4000
pN        .FILL x3200
pResult   .FILL x3201

          .END
