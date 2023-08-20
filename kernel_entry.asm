[bits 32]
[extern load_crumbs]
[extern main]

;
;	kernel_entry.asm - The kernel entry
;
;	Here we define the IDT macros, and call into the main kernel function.
; 	This is what we mean by "The Kernel". This program is stored at memory address 0x1000
;

; Tell the kernel to load the information needed.
call load_crumbs

call main  ; Call into our kernel code located at 0x1000
jmp $      ; Loop if kernel returns control to us.
