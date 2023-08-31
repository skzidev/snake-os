echo "Checking Dependencies..."

# Clunky way of checking for depedencies.
# GCC
if [[ "$(command -v gcc)" == ""  ]]; then
	printf "\e[31m\e[1mDependency GCC not found.\e[0m\n"
	echo Try: "sudo apt install build-essential"
	exit
fi
# LD
if [[ "$(command -v ld)" == ""  ]]; then
	printf "\e[31m\e[1mDependency LD not found.\e[0m\n"
	echo Try: "sudo apt install build-essential"
	exit
fi
# NASM
if [[ "$(command -v nasm)" == ""  ]]; then
	printf "\e[31m\e[1mDependency NASM not found.\e[0m\n"
	echo Try: "sudo apt-get install nasm"
	exit
fi

echo "Compiling kernel..."
# Compile our kernel to a .o file
gcc -m32 -fno-pie -ffreestanding -g -c kernel.c  -o obj/main.o

# Assemble our bootloader and kernel_entry point
nasm -f elf kernel_entry.asm -o obj/entry.o
nasm -f bin boot_sect.asm -o obj/boot.bin

# Link our kernel and kernel entrypoint
ld -m elf_i386 -o obj/kernel.bin -Ttext 0x1000 obj/entry.o obj/main.o -e main --oformat binary

# Error Detection.
# Check if it failed to link.
if [ ! -f ./obj/kernel.bin ]; then
	echo "Complication Failed."
	echo "Not Attempting to run."
	exit
fi

# Put together a final .bin file
cat obj/boot.bin obj/kernel.bin > bin/os.bin

# Check if requested not to open in VM.
if [ ! "$1" == "-nvm" ]; then
	if [[ "$(command -v qemu-system-x86_64)" == ""  ]]; then
		printf "\e[33m\e[1mQEMU is not installed.\e[0m\n"
		echo Compilation is finished, but testing is recommended.
		echo Try: "sudo apt-get install qemu-system"
		echo "To skip this step, use the -nvm flag when compiling"
		exit
	fi
	echo "Booting QEMU..."
	qemu-system-x86_64 -drive format=raw,file=bin/os.bin -display sdl -monitor stdio
else
	echo "Compilation completed."
fi
