TITLE Program 5     (program5_Ramirez_David.asm)

; Author: David Ramirez
; Course / Project ID: cs271-400       Date:5/28/17
; Description: This program is used to generate a user
; specified amount of random numbers from 100 to 999,
; display the list of unsorted generated numbers, sort 
; the list of generated numbers, calculate the median 
; of the list of generated numbers, and display the sorted
; list of generated numbers. 

INCLUDE Irvine32.inc

MAX = 200
MIN = 10
HI = 999
LO = 100

.data

intro1		BYTE	"Program 5 (Random Number List) by David Ramirez",0
intro2		BYTE	"This program generates a user specified amount of",0
intro3		BYTE	"random numbers from 100 to 999, displays the list",0
intro4		BYTE	"of unsorted generated numbers, sorts and displays  ",0
intro5		BYTE	"the list of generated number, and calculates and ",0
intro6		BYTE	"displays the median of the list of generated numbers.",0
data1		BYTE	"How many random numbers should be generated (max 200):",0
invalid		BYTE	"Invalid input, try again",0
title1		BYTE	"Unsorted List",0
title2		BYTE	"Sorted List",0
median		BYTE	"The median of the list is: ",0
space		BYTE	"   ",0
array		DWORD	MAX		DUP(?)
request		DWORD	?


.code

;Main procedure that sets up parameters for and calls all
;other procedures in order.
;receives: none
;returns: none
;preconditions: none
;registers changed: edx, eax, ebx, ecx
main PROC

call		Randomize

push		OFFSET intro1			;push arguments for introduction to stack and call
push		OFFSET intro2
push		OFFSET intro3
push		OFFSET intro4
push		OFFSET intro5
push		OFFSET intro6
call		introduction

push		OFFSET data1			;push arguments for getData to stack and call
push		OFFSET invalid
push		OFFSET request
call		getData

push		request					;push arguments for fillArray to stack and call
push		OFFSET array
call		fillArray

push		OFFSET space			;push arguments for displayList to stack and call
push		OFFSET title1
push		request
push		OFFSET array
call		displayList

push		OFFSET array			;push arguments for sortList to stack and call
push		request
call		sortList

push		OFFSET median			;push arguments for displayMedian to stack and call
push		request
push		OFFSET array
call		displayMedian

push		OFFSET space			;push arguments for displayList to stack and call
push		OFFSET title2
push		request
push		OFFSET array
call		displayList

exit								;exit to operating system

main ENDP



;Procedure to output introduction and program summary.
;receives: intro1 (reference), intro2 (reference), intro3 (reference),
;intro4 (reference), intro5 (reference), intro6 (reference)
;returns: none
;preconditions: none
;registers changed: edx
introduction PROC
push		ebp					;save value of ebp on stack
mov			ebp,esp				;use ebp as reference for accessing data on the stack

mov			edx, [ebp+28]		;display intro1
call		WriteString
call		CrLf
call		CrLf

mov			edx, [ebp+24]		;display intro2
call		WriteString
call		CrLf

mov			edx, [ebp+20]		;display intro3
call		WriteString
call		CrLf

mov			edx, [ebp+16]		;display intro4
call		WriteString
call		CrLf

mov			edx, [ebp+12]		;display intro5
call		WriteString
call		CrLf

mov			edx, [ebp+8]		;display intro6
call		WriteString
call		CrLf
call		CrLf

pop			ebp					;restore value of ebp
ret			24					;return to main and release parameters
introduction ENDP



;Procedure to prompt, validate, and save user integer input.
;receives: data1 (reference), invalid (reference), request (value)
;returns: request = user integer input
;preconditions: none
;registers changed: edx, eax, ebx
getData PROC
push		ebp					;save value of ebp on stack
mov			ebp,esp				;use ebp as reference for accessing data on the stack

mov			edx, [ebp+16]		;display data string
call		WriteString

jmp			afterInputLoop		;skip invalid input message 

inputLoop:
mov			edx, [ebp+12]		;display the invalid input string
call		WriteString
call		CrLf

afterInputLoop:
mov			eax, 0				;clear eax for use
call		Readint				;put user input in eax

cmp			eax, MIN			;jump to inputLoop if input too low
jb			inputLoop

cmp			eax, MAX			;jump to inputLoop if input too high
ja			inputLoop			

mov			ebx, [ebp+8]		;move address of request to ebx
mov			[ebx],	eax			;move value of eax to value pointer to by ebx
call		CrLf

pop			ebp					;restore value of ebp
ret			12					;return to main and release parameters
getData ENDP



;Procedure to fill array (of size specified by request) with 
;pseudo-randomly generated numbers.
;receives: request (value), array (reference)
;returns: array (filled with pseudo random numbers)
;preconditions: request contains user integer input
;registers changed: eax, ebx, ecx, edx
fillArray PROC
push		ebp					;save value of ebp on stack
mov			ebp, esp			;use ebp as reference for accessing data on the stack

mov			esi, [ebp+8]		;move address of arrary to esi
mov			ecx, [ebp+12]		;move value of request to ecx
mov			eax, 0				;clear eax for use for RandomRange

fill:
mov			eax, ((HI-LO)+1)	;move range to eax
call		RandomRange			;generates random number in range
add			eax, LO		
mov			[esi], eax			;move random number to array
add			esi, 4				;point esi to next DWORD in array
loop		fill

pop			ebp					;restore value of ebp
ret			8					;return to main and release parameters from stack

fillArray ENDP



;Procedure to sort array of psuedo-random numbers from 
;lowest value to highest value.
;receives: request (value), array (reference)
;returns: array (sorted from lowest to highest)
;preconditions: array is filled with psuedo-random numbers
;registers changed: eax, ebx, ecx, edx
sortList PROC
push		ebp					;save value of ebp
mov			ebp, esp			;use ebp as reference for accessing data on the stack


mov			edx, [ebp+8]		;move value of request to ecx for outter loop
dec			edx					;decrement edx for bubble sort


outLoop:
mov			ecx, edx			;move value of loop counter to ecx
mov			esi, [ebp+12]		;point esi to beginning of array

inLoop:
mov			eax, [esi]			;put value to compare in eax
add			esi, 4				;point esi to next DWORD in array

mov			ebx, [esi]			;put value to compare in ebx

cmp			eax, ebx			;jump to firstHigher if first number is higher
jae			firstHigher

mov			[esi], eax			;if second number , switch them in the array
mov			[esi-4], ebx

firstHigher:
loop		inLoop

dec			edx					;subtract 1 from edx for bubble sort
cmp			edx, 0				;if edx = 0, end the outter loop
je			endSort
jmp			outLoop				;complete outter loop

endSort:
pop			ebp					;restore value of ebp
ret			8					;return to main and release parameters from stack

sortList ENDP



;Procedure to find and display median value of sorted array.
;receives: request (value), array (reference), median (reference)
;returns: none
;preconditions: array of pseudo-random numbers is sorted 
;registers changed: eax, ebx,edx
displayMedian PROC
push		ebp					;save value of ebp on stack
mov			ebp,esp				;use ebp as reference for accessing data on the stack

mov			esi, [ebp+8]		;point esi to beginning of array
mov			eax, [ebp+12]		;move value of request to eax
mov			bl, 2				;divide by 2 to find middle value number in list
div			bl					
cmp			ah, 0
jne			oddNumber
mov			bl, 4				;multiply by 4 to find corresponding value in array
mul			bl
sub			eax, 4				;subtract by 4 to find middle number reference address (previous value was middle address+4)
mov			ebx, [esi+eax]		;move value corresponding to middle value of array to ebx
mov			eax, ebx			;move value from ebx to eax for display
jmp			evenNumber

oddNumber:
mov			bl, 4				;multiply by 4 to find corresponding value in array
mul			bl
mov			ebx, [esi+eax]		;move first middle value of array to ebx
sub			eax, 4
mov			ecx, [esi+eax]		;move second middle value of array to ecx
add			ebx, ecx			;add both middle values
mov			eax, ebx			;mov sum of both middle values to eax
mov			edx, 0				
mov			ebx, 2				;divide by 2 to find average of both middle numbers
div			ebx

evenNumber:
mov			edx, [ebp+16]		;move address of median string to edx for display
call		WriteString			;display median string
call		Writedec			;display median value
call		CrLf
call		CrLf

pop			ebp					;restore value of ebp
ret			12					;return to main and release parameters from stack

displayMedian ENDP



;Procedure to display array of psuedo-random numbers.
;receives: request (value), array (reference), title1 or title2 
;(reference), space (reference)
;returns: none
;preconditions: array is filled with pseudo-random numbers
;registers changed: eax, ebx, ecx, edx
displayList PROC
push		ebp					;save value of ebp on stack
mov			ebp, esp			;use ebp as reference for accessing data on the stack

mov			ebx, 0				;clear ebx for use in output count
mov			ecx, [ebp+12]		;move request value to ecx for loop
mov			esi, [ebp+8]		;move address of array to esi
mov			edx, [ebp+16]		;move address of title string to edx
call		WriteString			;display titles
call		CrLf
mov			edx, [ebp+20]		;move spaces string address to edx

displayLoop:
mov			eax, [esi]			;move value pointed to by esi to eax
add			esi, 4				;point esi to next element in list
call		WriteDec			;display value
call		WriteString			;display spaces
add			ebx, 1				;add 1 to count of displayed numbers
cmp			ebx, 10				;if number of displayed is 10, make new line
je			nextLine
jmp			afterNextLine

nextLine:
call		CrLf				;make new line
mov			ebx, 0				;clear ebx

afterNextLine:
loop		displayLoop			;loop for amount of elements in array
call		CrLf
call		CrLf

pop			ebp					;restore value of ebp
ret			12					;return to main and release parameters from stack

displayList ENDP

END main
