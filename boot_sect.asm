[org 0x7c00]

; Load Sectors
mov ah, 0x02
mov al, 0x2
int 0x13

KERNELLOC equ 0x1000
CODESEG equ gdt_code - gdt_start
DATASEG equ gdt_data - gdt_start

cli ; Disable Interrupts
lgdt [gdt_descriptor] ; GDT start address
mov eax, cr0
or eax, 1
mov cr0, eax ; Jump to Protected 32 bit mode
jmp CODESEG:start_protected_mode

jmp $

gdt_start:
	gdt_null:
		dd 0x0
		dd 0x0

	gdt_code:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10011010
		db 0b11001111
		db 0x0
	
	gdt_data:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10010010
		db 0b11001111
		db 0x0
	gdt_end:

	gdt_descriptor:
		dw gdt_end - gdt_start
		dd gdt_start

[bits 32]
start_protected_mode:
	mov ax, DATASEG
		mov ss, ax
		mov es, ax
		mov fs, ax
		mov gs, ax

		mov ebp, 0x90000
		mov esp, ebp

	jmp KERNELLOC

; Marking as bootable.
times 510-($-$$) db 0
dw 0xaa55
