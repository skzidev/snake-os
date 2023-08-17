[bits 16]
[org 0x7C00]

;
;	boot_sect.asm - The bootloader
;
;	This is where we read the sectors off the disk and run the OS
;	Note this isn't very secure, but for our intents and purposes it works just fine.
;	If it ain't broke don't fix it.
;

; Load the boot drive into a variable.
mov [BOOTDRIVE], dl

; Start loading the kernel
call load_kernel

; Start to load the kernel
load_kernel:
	                      ; Load the kernel's memory address into bx
	mov bx, KERNELOFFSET
	mov dh, 0x05          ; Put amount of sectors to load into dh
	mov dl, [BOOTDRIVE]   ; Put the boot drive back into dl
	call disk_load        ; Load more sectors From Disk

	mov ah, 0x00          ; Start setting video mode
	mov al, 0x13          ; 320x200 256 color graphics
	int 0x10

	cli                   ; Disable Interrupts to go into protected mode.
	lgdt [gdt_descriptor] ; Load the global descriptor table.
	
	mov eax, cr0          ; Start going into protected mode.
	or eax, 1
	mov cr0, eax          ; Jump to Protected 32 bit mode
	jmp CODESEG:start_protected_mode
	; Now we are in 32 bit mode.

	jmp $ ; Infinite loop just for good measure
; The Clear Screen Routine
clear_screen:
	pusha            ; Push A onto the stack

	mov ah, 0x07     ; Scroll al lines; 0 = all lines
	mov bh, 0x0f     ; set color to white on black
	mov cx, 0x00     ; row=0, col=0
	mov dx, 0x184f   ; row = 24, col = 79
	int 0x10         ; Call interrupt

	mov ah, 0x02     ; Set the cursor position
	mov dh, 0x00     ; Row
	mov dl, 0x00     ; Column
	mov bh, 0x00     ; Page number
	int 0x10         ; Call interrupt again

	popa             ; Pop A off the stack
	ret              ; Return from the subroutine
; The Disk Load Routine
disk_load:
	pusha             ; Push A onto the stack
	push dx           ; Push dx onto the stack
	mov ah, 0x02      ; read mode
	mov al, dh        ; read dh number of sects (set in load_kernel)
	mov cl, 0x02      ; read from sect 2 (1 = boot)
	mov ch, 0x00      ; cylinder 0
	mov dh, 0x00      ; head 0

	int 0x13          ; Call interrupt
	jc disk_error     ; Call subroutine on error

	pop dx            ; Pop dx off the stack
	cmp al, dh        ; Compare al and dh

	jne sectors_error ; Call subroutine for sector error
	popa              ; Pop A off the stack
	ret               ; Return from subroutine

; Error routines mentioned above
; For more details, the readme will help.
disk_error:
	              ; Error reading the sectors off the disk.
	mov ah, '1'   ; Error Number displayed on the screen
	jmp err_loop  ; Print the error message and loop.
sectors_error:
	              ; Didn't read all sectors needed off the disk.
	mov ah, '2'   ; Error Number displayed on the screen
	jmp err_loop  ; Print the error message and loop.
err_loop:
	call clear_screen  ; Call the clear screen routine
	mov dh, ah         ; Error Number to print
	mov ah, 0x0e       ; Teletype output mode
	mov al, 'E'        ; Print 'E'
	int 0x10
	mov al, 'r'        ; Print 'r' twice
	int 0x10
	int 0x10
	mov al, ' '        ; Print ' ' (space)
	int 0x10
	mov al, dh         ; Print Error Code provided in ah register
	int 0x10           ; Finish printing our message
	
	jmp $              ; Infinite loop.

; Constants
KERNELOFFSET equ 0x1000           ; Kernel Memory Address
CODESEG equ gdt_code - gdt_start  ; Code Segment Address
DATASEG equ gdt_data - gdt_start  ; Data Segment Address

; Global Descriptor Table
gdt_start:
	dq 0x0

	; Null segment
	gdt_null:
		dd 0x0
		dd 0x0

	; Code segment
	gdt_code:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10011010
		db 0b11001111
		db 0x0

	; Data segment
	gdt_data:
		dw 0xffff
		dw 0x0
		db 0x0
		db 0b10010010
		db 0b11001111
		db 0x0
	gdt_end:

	; GDT Descriptor
	gdt_descriptor:
		dw gdt_end - gdt_start
		dd gdt_start

; 32 bit protected mode.
[bits 32]
start_protected_mode:
	                  ; Using a flat memory model.
	mov ax, DATASEG   ; Set all segment regs to data segment
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	                  ; We can access anywhere in memory from here.
	
	mov ebp, 0x9000   ; Can't quite remember what this does.
	mov esp, ebp      ; Probably has to do with the flat memory model.

	call KERNELOFFSET ; Jump to the kernel. It takes everything from here.
	jmp $             ; In case the kernel hands back control to us, just loop.

; The boot drive variable.
BOOTDRIVE db 0

; Marking as bootable for the BIOS
times 510-($-$$) db 0
dw 0xaa55
