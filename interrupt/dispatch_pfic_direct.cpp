#include "interrupt.h"

extern interrupt::vector_t vectors_pfic[];

[[gnu::interrupt]]
void riscv_interrupt_handler() {
    uint32_t cause;
    asm("csrr %0, mcause" : "=r"(cause));

    uint32_t type = cause & 0x80000000;
    uint32_t code = cause & 0x7fffffff;

    (void)type;
    vectors_pfic[code]();
}

[[gnu::constructor(200)]]
void riscv_interrupt_init() {
    // Unlike WCH SDK, we're using direct mode, not vectored, presently
    asm volatile("csrw mtvec, %0" :: "r"(riscv_interrupt_handler));
}


// Should this go as an extra file in startup/entry_riscv_extra.cpp or something?
[[gnu::constructor(199)]]
void riscv_setup_extra() {
	// pipeline and cache?
	// https://github.com/openwch/ch32v307/issues/16
	asm volatile("csrw 0xbc0, %0" :: "r"(0x1f));

#if defined(CH32V23)
	// Enable HW Stack, Interrupt nesting(8n3p), hw stk overflow
	asm volatile("csrw 0x804, %0" :: "r"(0x1f));
#elif defined(CH58x)
	// enable HW Stack, Interrupt nesting(2n?p
	asm volatile("csrw 0x804, %0" :: "r"(0x3));
#else
#warning "You have a PFIC, on an unknown CPU? here be dragons!"
#endif

	// Enable floating point and interrupt
//   	li t0, 0x6088
//   	csrs mstatus, t0
	// Set FS to "Dirty" ("enable" FPU)
	// Set MPIE, Set MIE ("enable" interrupts)
	asm volatile("csrw mstatus, %0" :: "r"(0x6088));
}

