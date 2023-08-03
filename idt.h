typedef struct InterruptDescriptor {
	// For 32 bit protected mode, as That's what we're in
	uint16_t   isr_low;     // Lower i6 bits of ISR address
	uint16_t   kernel_cs;   // GDT segment sector CPU will load into CS before calling ISR
	uint8_t    reserved;    // Set to zero.
	uint8_t    attributes;  // Type and attributes.
	uint16_t   isr_high;    // Higher 16 bits of ISR address
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10)));
static idt_entry_t[256];

typedef struct {
	uint16_t   limit;
	uint32_t   base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

__attribute__(noreturn)
void exception_handler(void);
void exception_handler(){
	__asm__ volatile ("cli; hlt");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
	idt_entry_t* descriptor = &idt[vector];

	descriptor->isr_low      = (uint32_t)isr & 0xFFFF;
	descriptor->kernel_cs    = 0x08;
	descriptor->attributes   = flags;
	descriptor->isr_high     = (uint32_t)isr >> 16;
	descriptor->reserve      = 0;
}

extern void* isr_stub_table[];

void idt_init(void);
void idt_init(){
	idtr.base =  (uintptr_t)&idt[0];
	idtr.limit = (uint16_t) sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

	for(uint8_t vector = 0; vector < 32; vector ++){
		idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
		vectors[vector] = true;
	}

	__asm__ volatile ("lidt %0" : : "m"(idtr));
	__asm__ volatile ("sti");
}
