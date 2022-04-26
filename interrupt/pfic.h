#pragma once
/**
 * PFIC is a cross between CLIC and an ARM Cortex NVIC.
 * It's found on WCH "v3" and "v4" parts.
 */

#include "interrupt_enums.h"

#include <mmio/mmio.h>

struct PFIC_reg_t {
	volatile uint32_t ISR[4];
	uint32_t _reserved1[4];
	volatile uint32_t IPR[4];
	uint32_t _reserved2[4];
	volatile uint32_t ITHRESDR;
	uint32_t _reserved3;
	volatile uint32_t CFGR;
	volatile uint32_t GISR;
	volatile uint32_t VTFIDR;
	uint32_t _reserved4[3];
	volatile uint32_t VTFADDR[4];
	uint32_t _reserved5[36];
	/* Note: this latter section is register compatible with ARM NVIC! */
	volatile uint32_t IENR[4]; // 0x100
	uint32_t _reserved6[28];
	volatile uint32_t IRER[4]; // 0x180
	uint32_t _reserved7[28];
	volatile uint32_t IPSR[4]; // 0x200
	uint32_t _reserved8[28];
	volatile uint32_t IPRR[4]; // 0x280
	uint32_t _reserved9[28];
	volatile uint32_t IACTR[4]; // 0x300
	uint32_t _reserved10[60];
	volatile uint8_t IPRIOR[256]; // 0x400  // FIXME - TBD if we can access as 8bit wide!
	uint32_t _reserved11[516];
	volatile uint32_t SCTLR; // 0xd10 (analogous to SCB.SCR)
};


class PFIC_t : public mmio_ptr<PFIC_reg_t> {
	public:

        constexpr PFIC_t(uintptr_t offset) :
            mmio_ptr(offset) {}

        void enable(interrupt::irq n) const {
            ptr()->IENR[int(n) >> 5] = 1 << (int(n) & 0x1f);
        }

        void disable(interrupt::irq n) const {
            ptr()->IRER[int(n) >> 5] = 1 << (int(n) & 0x1f);
        }

        void set_priority(interrupt::irq n, uint8_t priority) const {
            ptr()->IPRIOR[int(n)] = priority;
        }
};
