TITLE Project 2     (cs271_project2.asm)

; Author: David Ramirez
; Course / Project ID  cs271-400                Date: 4/23/17
; Description: This program outputs the number of Fibonacci terms 
;			   corresponding to user input. The terms are outputted
;			   5 terms per line with at 5 spaces between terms. This
;			   program contains an introduction output and a 
;			   closing output.

INCLUDE Irvine32.inc

upperLimit = 46
lowerLimit = 1
term1 = 1
term2 = 2

.data

intro		BYTE	"Program 2 by David Ramirez",0
name1		BYTE	"What is your name?",0
name2		BYTE	"Hello and welcome to program 2, ",0
period		BYTE	".",0
userName	BYTE	33 DUP(0)										;string input by user
fPrompt		BYTE	"Please enter the number of Fibonacci terms ",0
fPrompt2	BYTE	"you would like to be displayed. (1-46)",0
display1	DWORD	?
temp1		DWORD	1												;holds value for next fib calculation
temp2		DWORD	1												;holds value for next fib calculation
fib			DWORD	?												;holds fib
termTrack	DWORD	?												;tracks number of fibs displayed 
outro		BYTE	"Now terminating program, good-bye. ",0
space		BYTE	"     ",0

.code
main PROC

;Introduction
	mov		edx, OFFSET intro			
	call	WriteString					;asks for name
	call	CrLf
	call	CrLf

	mov		edx, OFFSET name1			
	call	WriteString					;asks for name
	call	CrLf

	mov		edx, OFFSET userName		
	mov		ecx, 32						;ensures input fits in BYTE 33 DUP(0)
	call	ReadString					;saves input as 'userName'
	call	CrLF

	mov		edx, OFFSET name2
	call	WriteString					;greets user using name
	mov		edx, OFFSET userName
	call	WriteString
	mov		edx, OFFSET period
	call	WriteString
	call	CrLf
	call	CrLf

;User Instructions
	invalidInput:					;beginning of loop in case input is invalid
	mov		edx, OFFSET fPrompt			;displays prompt for user to enter number of 
	call	WriteString					;terms they would like to display
	call	CrLf
	mov		edx, OFFSET fPrompt2
	call	WriteString
	call	CrLf

;Get User Data
	call	ReadInt
	mov		display1, eax				;saves number terms input as 'display1'

	mov		eax, display1				;initiates loop if input greater than 46
	cmp		eax, upperLimit
	jg		invalidInput			    ;jump if greater than

	mov		eax, display1				;initiates loop if input less than 1
	cmp		eax, lowerLimit
	jl		invalidInput				;jump if less than

;Display Fibs
	mov		eax, temp1
	call	WriteDec					;output first fib
	mov		edx, OFFSET space
	call	WriteString

	mov		eax, display1
	cmp		eax, term1
	je		endProgram					;jumps to end of program if only 1 fib to be displayed
	
	mov		eax, temp1
	call	WriteDec					;output second fib
	mov		edx, OFFSET space
	call	WriteString

	mov		eax, display1
	cmp		eax, term2
	je		endProgram					;jumps to end of program if only 2 fibs to be displayed
	
	mov		eax, display1				
	sub		eax, 2						;subtracts 2 terms from amount of terms to display to
	mov		display1, eax				;account for the first 2 terms being 1 (not in loop)

	mov		eax, termTrack			
	add		eax, 2						;adds 2 to variable that tracks fibs displayed in order		
	mov		termTrack, eax				;to output 5 terms per line		

	mov		ecx, display1				;makes 'display1' loop counter

	numberTerms:						;start of loop for terms
	mov		eax, temp1
	add		eax, temp2					;add temp1 to temp2 to get fib
	call	WriteDec					;output fib
	mov		edx, OFFSET space
	call	WriteString

	mov		fib, eax					;saves fib

	mov		eax, termTrack				;increments variable to keep track of terms displayed
	add		eax, 1
	mov		termTrack, eax

	mov		eax, termTrack				;checks to see if number of terms displayed is divisible by 5
	mov		bl, 5						
	div		bl
	cmp		ah, 0
	je		newLine						;jump to 'newLine' if divisible by 5
	jne		continue					;jump to 'continue' if not
	
	newLine:
	call	CrLf
	
	continue:

	mov		eax, temp1					
	mov		temp2, eax					;makes temp2 = temp1
	
	mov		eax, fib
	mov		temp1, eax					;makes temp1 = fib

	loop	numberTerms					;loop for how many terms are to be displayed
	call	CrLf

;farewell
	mov		edx, OFFSET outro
	call	WriteString
	call	CrLf


	endProgram:

	





	



	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
