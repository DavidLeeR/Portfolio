TITLE Project 4              (project4_Ramirez_David.asm)

; Author: David Ramirez
; Course / Project ID: cs271-400                   Date: 5/14/17
; Description: This program calculates and dislays composite numbers. The number of
;    			composite numbers must be between 1 and 400, and is user
;				defined. The composite numbers are displayed 10 per line with 3 spaces 
;				between the numbers. This program includes extra credit options 1 and 2,
;				the output is aligned and more composite numbers are displayed one page at
;				a time.

INCLUDE Irvine32.inc

upperLimit = 400
lowerLimit = 0
upperLimit2 = 2
lowerLimit2 = 1
lastOutput = 963

.data

intro1		BYTE	"Program 4 (Composite Numbers) programmed by David Ramirez",0
extraCred1	BYTE	"**EC: option 1, this program aligns output columns",0
extraCred2	BYTE	"**EC: option 2, this program outputs more composite numbers, page by page",0
data1		BYTE	"Enter the number of composite numbers to be displayed.",0
data2		BYTE	"The number must be between 1 and 400 (inclusive).",0
data3		BYTE	"Enter the number of composite numbers to display [1-400]:",0
valid1		BYTE	"The entered input is not in range. Try again.",0
more1		BYTE	"Enter '1' if you would like to see more composite numbers (up to 800),",0
more2		BYTE	"or '2' to end the program.",0
outro1		BYTE	"Thank you for using Program 4 (Composite Numbers) by David Ramirez",0
space1		BYTE	"     ",0
space2		BYTE	"    ",0
space3		BYTE	"   ",0
number		DWORD	?
numCheck	DWORD	?
numBase		DWORD	?
divisor		DWORD	?
printCheck	DWORD	0
printCheck2	DWORD	0
choice		DWORD	?
last		DWORD	?
veryLast	DWORD	?
totalCheck	DWORD	0

.code

;Main procedure that calls all other procedures in order.
;receives: none
;returns: none
;preconditions: none
;registers changed: edx, eax, ebx, ecx

main PROC
	call introduction
	call getUserData
	call validate
	call showComposites
	call isComposite
	call moreComposites
	call validate2
	call farewell

	exit								; exit to operating system
main ENDP




;Procedure to output introduction and extra credit information.
;receives: intro1, extraCred1, and extraCred2 are global variables
;returns: none
;preconditions: none
;registers changed: edx

introduction PROC
	mov		edx, OFFSET intro1			;output intro string
	call	WriteString
	call	CrLf

	mov		edx, OFFSET extraCred1		;output extra credit option 1 info
	call	WriteString
	call	CrLf

	mov		edx, OFFSET extracred2		;output extra credit option 2 info
	call	WriteString
	call	CrLf
	call	CrLf

	ret
introduction ENDP




;Procedure to prompt and save user integer input.
;receives: data1, data2, and data3 are global variables
;returns: global number = user integer input
;preconditions: none
;registers changed: edx, eax

getUserData PROC
	mov		edx, OFFSET data1			;output instructions
	call	WriteString
	call	CrLf

	mov		edx, OFFSET data2			;output instructions part 2
	call	WriteString
	call	CrLf
	call	CrLf

	mov	edx, OFFSET data3				;output prompt for input
	call	WriteString

	call	ReadInt						;read input
	call	validate					;validate input
	mov		number, eax					;save input
	ret
getUserData ENDP




;Sub-procedure (of getUserData) to validate user integer input to be between 1 
;and 400 (inclusive).
;receives: eax; lowerLimit and Upperlimit are global constants; valid1 and data3 
;		   are global variables
;returns: eax (after input validation)
;preconditions: user integer input saved in eax
;registers changed: eax, edx

validate PROC
	cmp		eax, lowerLimit				;jump to input re-entry if input <= 0
	jle		badInput

	cmp		eax, UpperLimit				;jump to input re-entry if input > 400
	jg		badInput

	jmp		goodInput					;if input within bounds, jump to end validation

badInput:
	mov		edx, OFFSET valid1			;output string stating bad user input
	call	WriteString
	call	CrLf
		
	mov		edx, OFFSET data3			;output prompt for user input
	call	WriteString

	call	ReadInt						;read user input
	cmp		eax, lowerLimit				;jump to input re-entry if input <= 0
	jle		badInput

	cmp		eax, upperLimit				;jump to input re-entry if input >= 400
	jg		badInput

goodInput:
	ret

validate ENDP




;Procedure to output number of composite numbers specified by user in aligned columns.
;receives: number, numCheck, numBase, printCheck, space1, space2, and space3 are
;		   global variables; 4, 4, 1, 9, 99, 10, and 0 are literals
;returns: numCheck = numberto be evaluated for if it is composite or not;
;		  last = last composite number outputted
;preconditions: validated user input saved in number variable
;registers changed: ecx, ebx, eax, edx

showComposites PROC
	mov		ecx, number					;move input value to loop counter
	mov		numCheck, 4					;moves the first composite to variable holding possible composite numbers
	mov		numBase, 4					;moves the first composite to a variable to check numCheck against
mainLoop:
innerLoop:								;iterates until numCheck is a composite number
	call	isComposite
	mov		ebx, numCheck
	cmp		ebx, numBase				;if isComposite returned numCheck unincremented, it means numCheck is a composite
	je		print						;jump to print if numCheck is unincremented (composite)

	inc		numBase						;if numCheck has been incremented, it means numCheck is not a composite so increment numBase to find the next composite
	jmp		innerLoop					;restart loop to search for composite

print:
	cmp		ecx, 1						;compare ecx to 1, to see if it is the last loop
	je		lastNum						;if this is not the last loop, dont save the number
afterSave:
	mov		eax, numCheck			
	cmp		eax, 99						;if output number is greater than 99, jump to make much less space between
	jg		lessSpace2
	cmp		eax, 9						;if output number is greater than 9, jump to make less space between
	jg		lessSpace1
	
	call	writeDec					;if output less than 9, use maximum space between
	mov		edx, OFFSET space1
	call	WriteString
	inc		printCheck					;increment variable that keep count of outputted integers
	jmp		lineCheck					;jump to check if this line already has 10 outputted integers

resume:

	inc		numCheck					;increment numCheck and numBase to search for the next composite
	inc		numBase

	loop	mainLoop					;return to the loop iterated the amount of times specified by user input
	
	ret

lastNum:
	mov     eax, numCheck				;if this is the last loop, save the number
	mov		last, eax
	inc		last						;increment last so program will not repeat output if more numbers chosen to be displayed
	jmp		afterSave

lessSpace1:
	call	writeDec
	mov		edx, OFFSET space2			;make less space between outputted integers
	call	WriteString
	inc		printCheck					;increment variable that keep count of outputted integers
	jmp		lineCheck					;jump to check if this line already has 10 outputted integers

lessSpace2:
	call	writeDec
	mov		edx, OFFSET space3			;make even less space between outputted integers
	call	WriteString
	inc		printCheck					;increment variable that keep count of outputted integers
	jmp		lineCheck					;jump to check if this line already has 10 outputted integers

lineCheck:
	cmp		printCheck, 10				;if 10 integers have been outputted on the line, jump to call new line
	je		newLine
	jmp		resume						;if not, resume printing integers on this line

newLine:
	call	CrLf						;call new line
	mov		printCheck, 0				;make variable that keeps track of outputted integers per line 0 to start new line
	jmp		resume
showComposites ENDP




;Sub-procedure (of showComposites and showComposites2) to determine 
;if the number received is a composite number.
;receives: numCheck is a global variable; 0 and 2 are literals
;returns: numCheck (same value as recieved if composite, incremented
;		  if not composite)
;preconditions: number to be evaluated saved in numCheck
;registers changed: edx, eax, ebx

isComposite PROC
	mov		divisor, 2
	
checking:
	xor		edx, edx					;clear edx register to store remainder
	mov		eax, numCheck				;move number to check if composite to eax for dividing
	div		divisor						;divide by divisor (starts at 2)
	cmp		edx, 0						;compare remainder to 0
	je		endComposite				;jump to the end of this function for printing of number

	inc		divisor						;increment divisor if remainder found to != 0
	mov		ebx, divisor
	cmp		ebx, numCheck		    	;check to see if divisor is equal to number to check
	je		endNotComposite				;if divisor = number to check, it is a prime number

	jmp		checking

endComposite:
	ret									;return to calling function without incrementing numCheck, letting calling function know numCheck is composite

endNotComposite:
	inc		numCheck					;increment numCheck to let the calling function know that the previous numCheck was prime
	ret
isComposite ENDP




;Procedure to prompt and save user integer input to display more composite 
;numbers or quit the program. 
;receives: more1 and more2 are global variables; lastOutput is a global constant;
;		   1 is a literal
;returns: choice = user integer input
;preconditions: none
;registers changed: edx, eax

moreComposites PROC
more:
	call	CrLf
	call	CrLf						;output prompt part 1 for continuing number output
	mov		edx, OFFSET more1
	call	WriteString
	call	CrLf
	
	mov		edx, OFFSET more2			;output prompt part 2 for continuing number output
	call	WriteString
	call	CrLf

	call	ReadInt						;read and save user choice
	mov		choice, eax
	call	validate2					;validate input to be either 1 or 2

	cmp		choice, 1					;compare to see if choice is 1 or 2
	jg		return						;jump to end if user choice is 2, to quit the program

	call	showComposites2				;call function to show remaining composites, page by page

	cmp		veryLast, lastOutput		;compare last output to what should be the last output, jump to end program if match
	je		return	

	jmp		more						;repeat to show more composites if user chooses and limit not reached

return:
	ret

moreComposites ENDP




;Sub-procedure (of moreComposites) to validate user integer input to be either 1 or 2.
;receives: eax; lowerLimit2 and Upperlimit2 are global constants; valid1 and data3 
;		   are global variables
;returns: eax (after input validation)
;preconditions: user integer input saved in choice variable
;registers changed: eax, edx

validate2 PROC
	mov		eax, choice
	cmp		eax, lowerLimit2			;jump to input re-entry if input < 1
	jl		badInput2

	cmp		eax, UpperLimit2			;jump to input re-entry if input > 2
	jg		badInput2

	jmp		goodInput2					;if input within bounds, jump to end validation

badInput2:
	mov		edx, OFFSET valid1			;output string stating bad user input
	call	WriteString
	call	CrLf
		
	mov		edx, OFFSET data3			;output prompt for user input
	call	WriteString

	call	ReadInt						;read user input
	cmp		eax, lowerLimit				;jump to input re-entry if input <= 0
	jle		badInput2

	cmp		eax, upperLimit				;jump to input re-entry if input >= 400
	jg		badInput2

goodInput2:
	ret

validate2 ENDP




;Sub-procedure (of moreComposites) to output the next 100 composite numbers 
;in aligned columns.
;receives: last, space1, space2, and space3 are global variables; lastOutput
;		   is a global constant; 99, 9, 100, 0, and 10 are literals
;returns: last = last composite number outputted
;preconditions: last composite number outputted saved in last variable
;registers changed: ecx, ebx, eax, edx

showComposites2 PROC
	mov		eax, last
	mov		numCheck, eax				;moves the composite left off at to variable holding possible composite numbers
	mov		numBase, eax				;moves the composite left off at to a variable to check numCheck against
mainLoop2:
innerLoop2:								;iterates until numCheck is a composite number
	call	isComposite
	mov		ebx, numCheck
	cmp		ebx, numBase				;if isComposite returned numCheck unincremented, it means numCheck is a composite
	je		print2						;jump to print if numCheck is unincremented (composite)

	inc		numBase						;if numCheck has been incremented, it means numCheck is not a composite so increment numBase to find the next composite
	jmp		innerLoop2					;restart loop to search for composite

print2:
	mov		eax, numCheck	
	mov		veryLast, eax				;save the number to be outputted to see if it is the last (963)

	cmp		eax, 99						;if output number is greater than 99, jump to make much less space between
	jg		lessSpace22
	cmp		eax, 9						;if output number is greater than 9, jump to make less space between
	jg		lessSpace11
	
	call	writeDec					;if output less than 9, use maximum space between
	mov		edx, OFFSET space1
	call	WriteString
	inc		printCheck2					;increment variable that keep count of outputted integers
	inc		totalCheck
	jmp		lineCheck2					;jump to check if this line already has 10 outputted integers

resume2:

	inc		numCheck					;increment numCheck and numBase to search for the next composite
	inc		numBase

	cmp		totalCheck, 100				;compare to 100 (size of page)
	je		ending						;jump to end if page full (=100)

	cmp		veryLast, lastOutput		;compare last output to what should be the last output
	je		ending						;jump to end if match (means limit has been reached)

	jmp		mainLoop2					;return to the loop iterated the amount of times specified by user input

ending:
	mov		totalCheck, 0				;zero out totalCheck to represent a new page of 100
	mov		eax, numCheck
	mov		last, eax
	inc		last						;increment last so output doesn't repeat if more numbers to be outputted
	ret

lessSpace11:
	call	writeDec
	mov		edx, OFFSET space2			;make less space between outputted integers
	call	WriteString
	inc		printCheck2					;increment variable that keep count of outputted integers
	inc		totalCheck
	jmp		lineCheck2					;jump to check if this line already has 10 outputted integers

lessSpace22:
	call	writeDec
	mov		edx, OFFSET space3			;make even less space between outputted integers
	call	WriteString
	inc		printCheck2					;increment variable that keep count of outputted integers
	inc		totalCheck
	jmp		lineCheck2					;jump to check if this line already has 10 outputted integers

lineCheck2:
	cmp		printCheck2, 10				;if 10 integers have been outputted on the line, jump to call new line
	je		newLine2
	jmp		resume2						;if not, resume printing integers on this line

newLine2:
	call	CrLf						;call new line
	mov		printCheck2, 0				;make variable that keeps track of outputted integers per line 0 to start new line
	jmp		resume2

showComposites2 ENDP




;Procedure to display closing message.
;receives: outro1 is a global variable
;returns: none
;preconditions: none
;registers changed: edx

farewell PROC
	call	CrLf
	mov		edx, OFFSET outro1			;output closing message
	call	WriteString
	call	CrLf

	ret
farewell ENDP




END main
