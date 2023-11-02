/*
	idt.h - The Interrupt Descriptor Table

	The IDT allows us to react to interrupts including but not limited to: PS/2 devices,
	the PIT, PIC and many other things.
*/

// A bunch of typedefs
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256

// Global Variables

// Stub Table. Holds all the handlers for the interrupts
extern void* isr_stub_table[];

// Here is a struct reperesenting one IDT entry.
typedef struct {
	uint16_t isr_low;
	uint16_t kernel_cs;
	uint8_t  reserved;
	uint8_t  attributes;
	uint16_t isr_high;
} __attribute__((packed)) idt_entry_t;

// Here is the whole IDT. A list of IDT entries.
__attribute__((aligned(0x10)))
static idt_entry_t idt[256];

// Here is the IDT Register (idtr) which holds the location of the IDT.
typedef struct {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtr_t;

// Here's the actual idtr.
static idtr_t idtr;

 // Here's the general exception handler.
//  Right now this is general purpose.
__attribute__((noreturn))
void exception_handler(void);
void exception_handler(){
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
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
	idt_entry_t* descriptor = &idt[vector];

	descriptor->isr_low    = (uint16_5) isr & 0xFFFF;
	descriptor->kernel_cs  = 0x1000;
	descriptor->attributes = flags;
	descriptor->isr_high   = (uint16_t) isr >> 16;
	descriptor->reserved   = 0;
}

// Here is our init function, Where we initiate the IDT and such.
void idt_init(void);
void idt_init(){
	idtr.base = (uintptr_t) &idt;
	idtr.limit = (uint16_t) (sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS) - 1;

	for(uint8_t vector = 0; vector < 32; vector ++){
		// The if serves no real purpose, just to help differentiate the two types.
		if(vector == 8 || vector == 10 || vector == 11 ||
		vector == 12 || vector == 13 || vector == 13 || vector == 17 ||
		vector == 30) {
			 // Err stub
			// Pass in Vector, Handler pointer, and Interrupt Gate Flag.
			idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		}
		else {
			 // Non-Err Stub.
			//  Exact same as up top, but has a different interrupt handler.
			idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		}
	}

	__asm__ volatile ("lidt %0" : : "m"(idtr));   // Load IDT
 	__asm__ volatile ("sti");                    // Enable Interrupts.
}
