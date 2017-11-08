TITLE Program 1     (CS271_program1.asm)

; Author: David Ramirez
; Course / Project ID: CS271             Date: 4/16/17
; Description: This program displays the author name and program title, 
; prompts the user to enter two numbers, performs various calculations 
; on the numbers, and displays a terminating message. It also contains
; extra credit options 1, 2, and 3. The program repeats until the user
; decides to quit, validates the second number to be less than the first
; number, and displays the quotient as a floating point value rounded to
; the nearest .001.

INCLUDE Irvine32.inc


.data
first		DWORD	?					;all DWORD and WORD variables save integers
second		DWORD	?					;all BYTE variables hold strings
sum			DWORD	?
difference	DWORD	?
product		DWORD	?
quotient	DWORD	?
remainder	DWORD	?
thousand	WORD	1000
intro		BYTE	"           Program 1 by David Ramirez",0
ec1			BYTE	"**EC: option 1, Program repeats until user chooses to quit.",0
ec2			BYTE	"**EC: option 2, Program validates the second number ",0
ec2end		BYTE	"                to be less than the first.",0
ec3			BYTE	"**EC: option 3, Program calculates and displays the",0
ec3end		BYTE	"                quotient as a floating-point number ",0
ec3end2		BYTE	"				 rounded to the nearest .001.",0
prompt		BYTE	"Please enter 2 numbers to calculate their sum, ",0
promptend	BYTE	"difference, product, quotient, and remainder.",0
promptend1	BYTE	"Make sure the second number is less than the first.",0
prompt1		BYTE	"First number: ",0
prompt2		BYTE	"Second number: ",0
addSign		BYTE	" + ",0
subSign		BYTE	" - ",0
multSign	BYTE	" x ",0
divSign		BYTE	" / ",0
equalSign	BYTE	" = ",0
rmName		BYTE	" remainder ",0
quotientS	BYTE	"The quotient as a floating point value is: ", 0
remainderS	BYTE	"The remainder as a floating point value is: ", 0
terminate	BYTE	"Program 1 is now closing, good-bye.",0
redo		BYTE	"If you would like to repeat the program, enter '1'.",0
complete	BYTE	"If you would like to end the program, enter any other integer.",0

.code
main PROC

; Introduction
	mov		edx, OFFSET intro		
	call	WriteString				;output introduction and extra credit information
	call	CrLf
	mov		edx, OFFSET ec1
	call	WriteString				;output info for extra credit option 1
	call	CrLf
	mov		edx, OFFSET ec2
	call	WriteString				;output info for extra credit option 2
	call	CrLf
	mov		edx, OFFSET ec2end
	call	WriteString
	call	CrLf
	mov		edx, OFFSET ec3
	call	WriteString				;output info for extra credit option 3
	call	CrLf
	mov		edx, OFFSET ec3end
	call	WriteString				;output info for extra credit option 2
	call	CrLf
	call	CrLf

; Get the data
	beginning:
	mov		edx, OFFSET prompt		
	call	WriteString				;output prompt to tell user what program does
	call	CrLf
	mov		edx, OFFSET promptend
	call	WriteString
	call	CrLf
	secondLarge:
	mov		edx, OFFSET promptend1
	call	WriteString
	call	CrLf
	call	CrLf
	mov		edx, OFFSET prompt1		
	call	WriteString				;output prompt to enter first number
	call	ReadInt					
	mov		first, eax				;save first number in first
	mov		edx, OFFSET prompt2
	call	WriteString				;output prompt to enter second number
	call	ReadInt	
	mov		second, eax				;save second nuber in second

; Validate the second number to be less than the first
	mov		eax, first
	cmp		eax, second
	jle		secondLarge

; Calculate the required values
; add								;adds first number to second number and saves value in sum
	mov		eax, first
	add		eax, second
	mov		sum, eax

; subtract							;subtracts second number from first number and saves value in difference
	mov		eax, first
	sub		eax, second
	mov		difference, eax

; multiply							;multiplies first number by second and saves value in product
	mov		eax, first
	mov		ebx, second
	mul		ebx
	mov		product, eax

; divide
	mov		eax, first
	mov		ebx, second
	div		ebx
	mov		quotient, eax
	mov		remainder, edx

; divide as floats					;converts first integer and second integer to floats and divides them
	fild	first					;converts integer to float and loads on stack
	fild	second					;converts integer to float and loads on stack
	fdiv							;divides first number by second number
	fimul	thousand				;this and next 2 lines set precision to thousandths place
	frndint
	fidiv	thousand
	

;Report calculations
;report sum
	mov		eax, first
	call	WriteDec				;output first number
	mov		edx, OFFSET addSign
	call	WriteString				;output addition sign
	mov		eax, second
	call	WriteDec				;output second number
	mov		edx, OFFSET equalSign
	call	WriteString				;output equals sign
	mov		eax, sum
	call	WriteDec				;output sum
	call	CrLf

;report difference
	mov		eax, first
	call	WriteDec				;output first number
	mov		edx, OFFSET subSign
	call	WriteString				;output subtraction sign
	mov		eax, second
	call	WriteDec				;output second number
	mov		edx, OFFSET equalSign
	call	WriteString				;output equals sign
	mov		eax, difference
	call	WriteDec				;output difference
	call	CrLf

;report product
	mov		eax, first
	call	WriteDec				;output first number
	mov		edx, OFFSET multSign
	call	WriteString				;output subtraction sign
	mov		eax, second
	call	WriteDec				;output second number
	mov		edx, OFFSET equalSign
	call	WriteString				;output equals sign
	mov		eax, product
	call	WriteDec				;output product
	call	CrLf

; report quotient and remainder
	mov		eax, first
	call	WriteDec				;output first number
	mov		edx, OFFSET divSign
	call	WriteString				;output division sign
	mov		eax, second
	call	WriteDec				;output second number
	mov		edx, OFFSET equalSign
	call	WriteString				;output equals sign
	mov		eax, quotient
	call	WriteDec				;output quotient
	mov		edx, OFFSET rmName		
	call	WriteString				;output descripton for remainder
	mov		eax, remainder
	call	WriteDec				;output remainder
	call	CrLf

; report quotient as float
	mov		edx, OFFSET quotientS
	call	WriteString
	call	WriteFloat
	call	CrLf
	call	CrLf


	
; Repeat program based on user choice
	mov		edx, OFFSET redo
	call	WriteString				;output prompt for repeating program
	call	CrLf
	mov		edx, OFFSET complete	
	call	WriteString
	call	CrLf					;output prompt for ending program
	call	ReadInt
	cmp		eax, 1
	je		beginning


; Say goodbye
	mov		edx, OFFSET terminate
	call	WriteString
	call	CrLf

	exit	; exit to operating system
main ENDP


END main
