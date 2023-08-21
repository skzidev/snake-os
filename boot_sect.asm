[bits 16]
[org 0x7C00]

;
;	boot_sect.asm - The bootloader
;
;	This is where we read the sectors off the disk and run the OS
;	Note this isn't very secure, but for our intents and purposes it works.
;	If it ain't broke don't fix it.
;

; Load the boot drive into a variable.
mov [BOOTDRIVE], dl

; Start loading the kernel
call load_kernel

; Start to load the kernel
load_kernel:
	                      ; I was planning on calculating how many sectors to
	                      ; load on the fly so that's why it's here.
	mov bx, KERNELOFFSET  ; Load the kernel's memory address into bx
	mov dh, SECTORS       ; Put amount of sectors to load into dh
	mov dl, [BOOTDRIVE]   ; Put the boot drive back into dl
	call disk_load        ; Load more sectors From Disk

	mov ah, 0x00          ; Start setting video mode
	mov al, 0x13          ; 320x200 256 color graphics
	int 0x10              ; Call the Interrupt
						  ; Starting entry to 32 bit mode
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
	mov bh, 0x0C     ; set color to red on black
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
	mov ah, 0x02      ; Tell the BIOS we want to read more sectors
	mov al, dh        ; Read `dh` number of sectors (see load_kernel)
	mov cl, 0x02      ; Start from sector 2, as sect 1 is the boot-sector
	mov ch, 0x00      ; Cylinder 0
	mov dh, 0x00      ; Head 0

	int 0x13          ; Call interrupt
	jc disk_error     ; Call subroutine on error

	pop dx            ; Pop dx off the stack
	cmp al, dh        ; Compare al and dh
	jne sectors_error ; Jump to the sectors error routine
	
	popa              ; Pop A off the stack
	ret               ; Return from subroutine
; Error routines mentioned above
; For more details, the readme will help.
disk_error:
	                 ; Error reading the sectors off the disk.
	                 ; Likely a compilation issue, or disk couldn't
	                 ; spin up fast enough
	                 
	mov ah, '1'      ; Error Number displayed on the screen
	jmp err_msg      ; Print the error message and loop.
sectors_error:
	                 ; Didn't read all sectors needed off the disk.
	mov ah, '2'      ; Error Number displayed on the screen
	jmp err_msg      ; Print the error message and loop.
print_err:
	; If you're wondering why I didn't use the newfangled print_more
	; label, It requires a bunch more effort to get working, So I decided not
	; to bother. I may later, of course, but not right now.
	
	mov cl, 0        ; CL is the counter register.
	mov dh, ah       ; move the error number to print into dh
	mov ah, 0x0e     ; Interrupt Teletype output mode.
	mov al, 'E'      ; Print 'E'
	int 0x10
	mov al, 'r'      ; Print 'r' twice
	int 0x10
	int 0x10
	mov al, ' '      ; Print ' ' (space)
	int 0x10
	mov al, dh       ; Print Error Code provided in ah register
	int 0x10         ; Finish printing our message

	call print_more  ; Print 'Learn More' message

	ret              ; Return from subroutine
print_more:
	mov al, 0x0d     ; Carriage Return
	int 0x10
	mov al, 0x0a     ; Newline
	int 0x10
	cmp dh, '1'
	je err_one_message
	cmp dh, '2'
	je err_two_message
err_two_message:
	mov bx, err_two  ; Print the first error message
	call print_loop  ; Call the message loop
err_one_message:
	mov bx, err_one  ; Print the second error message
	call print_loop  ; Call the message loop
print_loop:
	mov al, [bx]     ; Get the character we want to print
	int 0x10         ; Print the character
	cmp al, 0        ; Check if string has ended 
	je err_loop      ; Jump to the err loop if we finished the string
	inc bx           ; Inc bx to get the next character
	jmp print_loop   ; Loop again to print another character.
err_msg:
	call clear_screen ; Call the clear screen routine
	call print_err    ; Print the error message.
	call err_loop     ; Jump to the loop
err_loop:
	mov ah, 0x01
	mov cx, 0x2607
	int 0x10
	jmp $             ; Infinite loop.
; Constants
KERNELOFFSET equ 0x1000           ; Kernel Memory Address
CODESEG equ gdt_code - gdt_start  ; Code Segment Address
DATASEG equ gdt_data - gdt_start  ; Data Segment Address
SECTORS equ 0x05

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
; Learn More String
err_one:
	db "Kernel was not found.", 0
err_two:
	db "Drive could not be read.", 0

; Marking as bootable for the BIOS
times 510-($-$$) db 0
dw 0xaa55
