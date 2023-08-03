[bits 16]
[org 0x7C00]

mov [BOOTDRIVE], dl

; call clear_screen ; Clear screen
call load_kernel

load_kernel:
	mov bx, KERNELOFFSET
	mov dh, 0x05
	mov dl, [BOOTDRIVE]
	; mov dl, 0x80
	call clear_screen     ; Clear Screen
	call disk_load        ; Load From Disk

	mov ah, 0x00          ; Start setting video mode
	mov al, 0x13          ; 320x200 256 color graphics
	int 0x10

	cli                   ; Disable Interrupts
	lgdt [gdt_descriptor] ; GDT start address
	mov eax, cr0
	or eax, 1
	mov cr0, eax          ; Jump to Protected 32 bit mode
	jmp CODESEG:start_protected_mode

	jmp $

clear_screen:
	pusha

	mov ah, 0x07     ; Scroll al lines; 0 = all
	mov bh, 0x0f     ; white on black
	mov cx, 0x00     ; row=0, col=0
	mov dx, 0x184f   ; row = 24, col = 79
	int 0x10         ; Call interrupt

	mov ah, 0x02
	mov dh, 0x00
	mov dl, 0x00
	mov bh, 0x00
	int 0x10

	popa
	ret

disk_load:
	pusha
	push dx
	mov ah, 0x02 ; read mode
	mov al, dh   ; read dh number of sects
	mov cl, 0x02 ; read from sect 2 (1 = boot)
	mov ch, 0x00 ; cylinder 0
	mov dh, 0x00 ; head 0

	int 0x13
	jc disk_error

	pop dx
	cmp al, dh

	jne sectors_error
	popa
	ret

disk_error:
	mov ah, '1' ; Error Code
	jmp err_loop
sectors_error:
	mov ah, '2' ; Error Code
	jmp err_loop
err_loop:
	call clear_screen
	mov dh, ah ; Print Error Message
	mov ah, 0x0e
	mov al, 'E'
	int 0x10
	mov al, 'r'
	int 0x10
	int 0x10
	mov al, ' '
	int 0x10
	mov al, dh ; Print Error Code
	int 0x10
	
	jmp $ ; create infinite loop

; Constants
KERNELOFFSET equ 0x1000
CODESEG equ gdt_code - gdt_start
DATASEG equ gdt_data - gdt_start

gdt_start:
	dq 0x0

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
	; Load the kernel
	mov ax, DATASEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x9000
	mov esp, ebp

	call KERNELOFFSET
	jmp $

BOOTDRIVE db 0

; Marking as bootable.
times 510-($-$$) db 0
dw 0xaa55
