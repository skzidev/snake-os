/*
	idt.h - The Interrupt Descriptor Table

	The IDT allows us to access interrupts, including the PIT, Keyboard, Mouse, etc.
	All things that trigger interrupts are made usable once this is fully implemented.
	I admittedly don't know a whole bunch about this but I know enough to make an
	educated guess about what everything is.
*/
// The IDT entry I have here should be 64 bytes in size.
#define IDT_MAX_DESCRIPTORS 256
#define IDT_ENTRY_BYTE_SIZE 64

// Types needed.
typedef unsigned char uint8;             // Just a byte I believe.
typedef unsigned short int uint16;      //  Two bytes in one type.
typedef unsigned int uint32;           //   Four Bytes in one type.
typedef unsigned long int uint64;     //    Eight Bytes in one type.
typedef unsigned long uintptr;       //     Enough space to hold a pointer.

// Global Variables

// Stub Table. Holds all the handlers for the interrupts
extern void* isr_stub_table[];
// Holds a list of "true" booleans. No Idea why it's here.
// int vectors[256];

// Here is a struct reperesenting one IDT entry.
typedef struct {
	uint16 isr_low;
	uint16 kernel_cs;
	uint8  reserved;
	uint8  attributes;
	uint16 isr_high;
} __attribute__((packed)) idt_entry_t;

// Here is the whole IDT. A list of IDT entries.
__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

// Here is the IDT Register (idtr) which holds the location of the IDT.
typedef struct {
	uint16 limit;
	uint32 base;
} __attribute__((packed)) idtr_t;

// Here's the actual idtr.
static idtr_t idtr;

 // Here's the general exception handler.
//  Right now this is general purpose.
__attribute__((noreturn))
void exception_handler(void);
void exception_handler(){
	__asm__ volatile ("cli; hlt");
	  // Silence GCC Warning until I find a better fix.
	 //  I know This looks confusing because I just halted,
	//   but it's a work in progress
	for(;;){}
}

void interrupt_handler(void);
void interrupt_handler(){
	 // I need to find something better to do.
	// General exception handler
	for(;;){}
}

  // Here is the function that will config any IDT entry we throw at it.
 //  I'm getting warnings in my editor for setting isr_low and isr_high.
//   It says casting to another type but GCC is not giving me a warning. 
void idt_set_descriptor(uint8 vector, void* isr, uint8 flags);
void idt_set_descriptor(uint8 vector, void* isr, uint8 flags){
	idt_entry_t* descriptor = &idt[vector];

	descriptor->isr_low    = (uint32) isr & 0xFFFF;
	descriptor->kernel_cs  = 0x1000;
	descriptor->attributes = flags;
	descriptor->isr_high   = (uint32) isr >> 16;
	descriptor->reserved   = 0;
}

// Here is our init function, Where we initiate the IDT and such.
void idt_init(void);
void idt_init(){
	idtr.base = (uint32) &idt[0];
	idtr.limit = (uint16) IDT_ENTRY_BYTE_SIZE * IDT_MAX_DESCRIPTORS - 1;

	for(uint8 vector = 0; vector < 32; vector ++){
		idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		// vectors[vector] = 1;
	}

	__asm__ volatile ("lidt %0" : : "m"(idtr)); // Load IDT
	__asm__ volatile ("sti"); // Enable Interrupts
}
