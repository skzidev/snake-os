# Compile our kernel to a .o file
gcc -m32 -fno-pie -ffreestanding -g -c kernel.c  -o obj/main.o

# Assemble our bootloader and kernel_entry point
nasm -f elf kernel_entry.asm -o obj/entry.o
nasm -f bin boot_sect.asm -o obj/boot.bin

# Link our kernel and kernel entrypoint
ld -m elf_i386 -o obj/kernel.bin -Ttext 0x1000 obj/entry.o obj/main.o -e main --oformat binary

# Put together a final .bin file
cat obj/boot.bin obj/kernel.bin > bin/os.bin

# Load up our bin file in QEMU
qemu-system-x86_64 -drive format=raw,file=bin/os.bin -display sdl
# -s -S
