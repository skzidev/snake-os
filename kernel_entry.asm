[bits 32]
; Get the main, interrupt_handler, and exception_handler functions.
[extern main]
[extern exception_handler]
[extern interrupt_handler]

;
;	kernel_entry.asm - The kernel entry
;
;	Here we define the IDT macros, and call into the main kernel function.
;	This makes sure that if the C function "main" is ever moved,
;	it will adjust to ensure it works. Curtosy of the linker.
;

; Setting up the stack

; Load the C part of the kernel.
call main  ; Call into the C kernel.
jmp $

; IDT Macros
%macro isr_err_stub 1
isr_stub_%+%1:
    ; call exception_handler
    jmp $  ; Loop when an exception is thrown
	iret 
%endmacro
%macro isr_no_err_stub 1
isr_stub_%+%1:
	call interrupt_handler
	iret
%endmacro

; Exception handlers
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

; ISR Stub Table
global isr_stub_table  ; Define the table.
isr_stub_table:
%assign i 0            ; int i = 0;
%rep    32             ; while(i < 32) {
    dd isr_stub_%+i    ; 	isr_stub_${i} = interrupt_handler;
%assign i i+1          ; 	i ++
%endrep                ; }
