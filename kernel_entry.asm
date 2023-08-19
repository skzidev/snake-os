[bits 32]
[extern main]

;
;	kernel_entry.asm - The kernel entry
;
;	Here we define the IDT macros, and call into the main kernel function.
; 	This is what we mean by "The Kernel". This program is stored at memory address 0x1000
;

; IDT Macros and stubs. 

%macro isr_err_stub 1
isr_stub_%+%1:
    call exception_handler
    iret 
%endmacro
; In case it's not an error
%macro isr_no_err_stub 1
isr_stub_%+%1:
    call exception_handler
    iret
%endmacro
global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
    dd isr_stub_%+i
%assign i i+1 
%endrep

extern exception_handler
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

call main  ; Call into our kernel code located at 0x1000
jmp $      ; Loop if kernel returns control to us.
