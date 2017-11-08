TITLE Program 6     (Program6_Ramirez_David.asm)

; Author: David Ramirez
; Course / Project ID: cs271-400            Date: 6/11/17
; Description: This program displays a list of integers, their sum, 
; and their average from user input. The I/O procedures and macros
; are custom coded. 

INCLUDE Irvine32.inc


;getString macro that saves user input as a string.
;receives: word (address of string to place input into), prompt (to tell user to enter number)
;returns: address of "word" string holds user input
;preconditions: none
;registers changed: edx, eax, ecx
getString		MACRO	word,prompt
	push	edx							;save registers used onto stack
	push	ecx
	push	eax

	mov		edx, prompt					;display prompt 1
	call	WriteString

	mov		edx, word					;move address of input into edx
	mov		eax, SIZES 
	mov		ecx, eax					;set max size
	call	ReadString					;read user input (save to input)


	pop eax								;restore registers used
	pop ecx
	pop edx
endm


;displayString macro that displays a string from memory.
;receives: word (address of string to write)
;returns: none
;preconditions: none
;registers changed: edx, 
displayString	MACRO	word
	push	edx							;save register used on stack

	mov		edx, word					;move address of input to edx
	call	WriteString					;display input

	pop		edx							;restore variable used
endm



MAX_INPUT = 10							;max size of array
SIZES = 30								;maxe size of bytes per array element



.data

intro1		BYTE	"Program 6A (low-level I/O procedures) by David Ramirez.",0
intro2		BYTE	"This Program takes 10 user inputted unsigned decimal integers",0
intro3		BYTE	"and displays a list of the integers, their sum, and their average.",0
intro4		BYTE	"The integers entered must be small enough to fit in 32 bits.",0
prompt1		BYTE	"Enter an unsigned integer: ",0
error		BYTE	"The input entered is invalid, try again",0
sum			BYTE	"The sum of the entered numbers is: ", 0
average		BYTE	"The average of the entered numbers is: ",0
list		BYTE	"The entered numbers are: ",0
comma		BYTE	", ", 0
string1		BYTE	15			DUP(?)
array		DWORD	MAX_INPUT	DUP(?)	
average1	DWORD	?
sum1		DWORD	?
check		DWORD	0
input		BYTE 	SIZES+1		DUP(?)



.code

;Main procedure that sets up parameters for and calls all
;other procedures in order.
;receives: none
;returns: none
;preconditions: none
;registers changed: edx, eax, ebx, ecx
main PROC
	push	OFFSET intro1				;push variables for and call Intro proc (display intro)
	push	OFFSET intro2
	push	OFFSET intro3
	push	OFFSET intro4
	call	Intro

	mov		ecx, 10						;move 10 to ecx for loop

	repeat10:
	push	ecx
	push	check

	push	OFFSET error
	push	OFFSET prompt1				;push variables for and call ReadVal proc (save user input as string and convert to int)
	push	OFFSET input
	push	OFFSET array
	call	ReadVal

	pop		ecx
	add		check, 4
	loop	repeat10					;loop for amount of integers needed from user

	
	push	OFFSET sum1					;push variables for and call Calculate proc (calculate sum and average of user input)
	push	OFFSET average1
	push	OFFSET array
	call	Calculate

	push	OFFSET comma				;push variables for and call WriteVal proc (convert user input int to string and display)
	push	OFFSET string1			
	push	OFFSET array			
	push	OFFSET list				
	push	OFFSET sum				
	push	OFFSET average		
	push	sum1					
	push	average1				
	call	WriteVal
	exit								; exit to operating system
main ENDP



;Intro procedure that outputs the intro message
;receives: intro1 (reference), intro2 (reference), intro3 (reference), intro4 (reference)
;returns: none
;preconditions: none
;registers changed: edx, 
Intro PROC
	push	ebp							;save value of ebp
	mov		ebp, esp					;set esp for accessing variables
	push	edx							;save value of edx

	displayString	[ebp+20]			;display intro 1
	call	CrLf

	displayString	[ebp+16]			;display intro2
	call	CrLf

	displayString	[ebp+12]			;display intro3
	call	CrLf

	displayString	[ebp+8]				;display intro4				
	call	CrLf
	call	CrLf

	pop		edx							;restore edx
	pop		ebp							;restore value of ebp
	ret		16							;pop all variables used off stack and return
Intro ENDP



;ReadVal proc that gets user input as a string, converts user input to an integer, validates
;user input, and saves user input in an array as integers. The ReadVal proc uses the getString
;proc get get user input as a string.
;receives: array (reference), input (reference), prompt1 (reference), error (reference)
;returns: array holds user input
;preconditions: none
;registers changed: eax, ebx, ecx, edx 
ReadVal PROC
	push		ebp						;save value of ebp
	mov			ebp, esp				;set esp for accessing variables
	pushad								;save values of registers

	mov			ebx, 0					;clear ebx
	mov			eax, 0					;clear eax

	front:
	getString		[ebp+12],[ebp+16]	;save user input as string

	mov			ecx, SIZES				;move max size of string to ecx for loop
	mov			esi, [ebp +12]			;move offset input into esi

	eachByte:
	lodsb								;move byte pointed to by esi into ax
	cmp			ax, 0					;compare ax to null (if null = end of string)
	je			finish
	cmp			ax, 10					;compare ax to 10 (if end line = end of string)
	je			finish
		
	cmp			ax, 48					;if al below ascii code for int, jump
	jb			outRange
	cmp			ax, 57					;if al above ascii code for int, jump
	ja			outRange

	sub			ax, 48					;convert to int if valid
	add			ebx, eax				;add int to ebx
	cmp			ecx, 1					;jump to end if this is last digit of input
	je			finish

	mov			eax, ebx				;if not last digit, move number to eax
	mov			edx, 10					;multiply by 10
	mul			edx
	jc			outRange				;jump to error message if number too large
	mov			ebx, eax				;move number back to ebx

	mov			eax, 0					;clear eax
	loop		eachByte				;loop for each byte of input

	outRange:
	mov			edx, [ebp+20]			;move offset error string to edx
	call		WriteString				;display error string
	call		CrLf
	mov			ebx, 0					;clear ebx
	jmp			front					;jump back to prompt for input again

	finish:
	mov			esi, [ebp+8]			;set esi to start of array
	mov			ecx, [ebp+24]					

	add			esi, ecx				;point esi to next element of array
	mov			eax, ebx				;move quotient to eax
	mov			ebx, 10
	div			ebx						;divide by 10 
	mov			ebx, eax				;move quotient to ebx
	mov			[esi], ebx			    ;move number to element

	popad								;restore registers
	pop			ebp						;restore ebp
	ret			20						;pop all variables used and return
ReadVal ENDP



;Calculate proc that calculates and saves the sum and average of user integer input.
;receives: array (reference), average1 (reference), sum1 (reference)
;returns: average1 holds average of user input as an integer, sum1 holds the sum of 
;user input as an integer
;preconditions: array holds user input as integers
;registers changed: eax, ebx, ecx, edx 
Calculate PROC
	push		ebp						;save value of ebp and registers
	mov			ebp, esp				;move esp to ebp for referrence
	pushad								;save registers

	mov			ecx, 10					;move 10 to ecx for loop
	mov			eax, 0				    ;clear eax

	mov			esi, [ebp+8]			;move address of array to esi
	jmp			firstTime				;if first element of array needed, do not add 4 to esi
	addNumbers:
	add			esi, 4					;add 4 to esi to point to next element
	firstTime:
	add			eax, [esi]				;add elements of array
	loop		addNumbers				;loop for amount of elements

	mov			edx, 0					;clear edx
	mov			edx, [ebp+16]			;move address of variable sum to edx
	mov			[edx], eax				;move added numbers to variable sum

	mov			edx, 0					;clear edx
	mov			ebx, 10					;move 10 to ebx to divide sum for average
	div			ebx						;divide sum by 10
	mov			edx, [ebp+12]			;move address of variable average to edx
	mov			[edx], eax				;move quotient to variable average

	popad								;restore registers
	pop			ebp						;restore ebp
	ret			12						;free all parameters and return
Calculate ENDP



;WriteVal proc that converts user integer input (as well as the average and sum of user input)
;to a string and displays the string. The WriteVal proc uses the ConvertInt proc to convert user
;integer input to a string and the displayString macro to display the converted strings.
;receives: average1 (value), sum1 (value), average (reference), sum (reference), list (reference),
;array (reference), string1 (reference), comma (reference)
;returns: none
;preconditions: array holds user integer input, sum1 holds sum of user input, average1 holds
;average of user input
;registers changed: eax, ebx, ecx, edx 
WriteVal PROC
	push		ebp						;save value of ebp
	mov			ebp, esp				;move esp to ebp for reference
	pushad								;save values of registers

	displayString	[ebp+24]			;display user input list statement


	mov			esi, [ebp+28]			;point esi to first element in array
	mov			ebx, [esi]				;move value of element of array to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]				
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 4					;point esi to 2nd element in array
	mov			ebx, [esi]				;move value of 2nd element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 8					;point esi to 3rd element in array
	mov			ebx, [esi]				;move value of 3rd element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 12					;point esi to 4th element in array
	mov			ebx, [esi]				;move value of 4th element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 16					;point esi to 5th element in array
	mov			ebx, [esi]				;move value of 4th element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 20					;point esi to 6th element in array
	mov			ebx, [esi]				;move value of 6th element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array	
	add			esi, 24					;point esi to 7th element in array
	mov			ebx, [esi]				;move value of 7th element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 28					;point esi to 8th element in array
	mov			ebx, [esi]				;move value of 8th element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 32					;point esi to 9th element in array
	mov			ebx, [esi]				;move value of 9th element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma

	mov			esi, [ebp+28]			;point esi to beginning of array
	add			esi, 36					;point esi to 10th element in array
	mov			ebx, [esi]				;move value of 10th element to ebx

	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display resulting string

	displayString	[ebp+36]			;display comma
	call		CrLf
	call		CrLf

	displayString	[ebp+20]			;display sum statement

	mov			ebx, [ebp+12]			;move value of sum variable to ebx
	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display sum as string
	call		CrLf
	call		CrLf

	displayString	[ebp+16]			;display average statement

	mov			ebx, [ebp+8]			;move value of average variable to ebx
	push		ebx						;push variables for and call ConvertInt proc (converts int to string)
	push		[ebp+32]
	call		ConvertInt
	displayString	[ebp+32]			;display average as string
	call		CrLf
	call		CrLf

	popad								;restore registers
	pop			ebp						;restore ebp
	ret			32						;return and release all parameters

WriteVal ENDP



;ConvertInt proc that converts integer to a string and saves the string. 
;receives: ebx (value to be converted), string1 (reference to string to place output in)
;returns: string1 holds converted integer
;preconditions: ebx hols integer to convert
;registers changed: eax, ebx, ecx, edx 
ConvertInt	PROC
	push	ebp							;save value of ebp
	mov		ebp, esp					;set esp to ebp for reference
	pushad								;save values of registers

	mov		edi, [ebp+8]				;point edi to string to save output to 
	mov		eax, [ebp+12]				;move value to be converted to eax

	mov		ecx,0						;clear ecx
	std									;set direction flag so that edi decrements instead of increments (working back to front)

	keepDividing:		
	mov			ebx, 10					;move 10 to ebx for dividing
	mov			edx,0					;clear edx

	div			ebx						;divide value by 10
	cmp			eax, 0					;compare value to 0 (if 0, then end of value)

	jbe			lastDigit			
	add			ecx,1					;add 1 to ecx to count digits in value	
	jmp			keepDividing			;keep dividing if not end of value

	lastDigit:	
	
	add			ecx,1					;add 1 to ecx for null terminator
	add			edi, ecx				;add length of value (plus terminator) to edi to point edi to end of string
	
	mov			al,0					;clear al		
	stosb								;load 0 into end of string

	mov			eax, [ebp+12]			;move value to be converted to eax
	
	keepMakingString:
	mov			edx, 0					;clear edx
	div			ebx						;divide value to be converted by 10

	push		ecx						;save value of ecx
	mov			ecx, 0					;clear ecx
	mov			ecx, eax				;move quotient to ecx

	add			edx, 48					;add 48 to remainder to get ascii int value
			
	mov			al, dl					;move remainder to al	
	stosb								;move remainder to string
	mov 		eax, ecx				;mov quotient back to eax
	pop			ecx						;resotre ecx
	loop		keepMakingString		;keep looping until string complete (ecx == 0 [ie. at beginning of string])

	popad								;restore registers
	pop			ebp						;restore ebp
	ret			8						;release parameters and return
ConvertInt	ENDP		

END main
