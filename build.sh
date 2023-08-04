gcc -m32 -fno-pie -ffreestanding -g -c kernel.c  -o obj/main.o

nasm -f elf kernel_entry.asm -o obj/entry.o
nasm -f bin boot_sect.asm -o obj/boot.bin

ld -m elf_i386 -o obj/kernel.bin -Ttext 0x1000 obj/entry.o obj/main.o -e main --oformat binary

cat obj/boot.bin obj/kernel.bin > bin/os.bin

qemu-system-x86_64 -drive format=raw,file=bin/os.bin -display sdl -s -S
