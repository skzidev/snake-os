gcc -ffreestanding -g -c main.c -o main.o

./nasm -f bin boot_sect.asm -o boot.bin

ld -o kernel.bin -Ttext 0x1000 main.o --oformat binary

cat boot.bin kernel.bin > os.bin

qemu-system-x86_64 os.bin
