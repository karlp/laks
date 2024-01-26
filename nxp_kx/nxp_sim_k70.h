#pragma once

#include <mmio/mmio.h>
#include "sim_enums.h"

struct NXP_SIM_K70_reg_t {
	volatile uint32_t SOPT1;
	volatile uint32_t SOPT1_CFG;
	uint32_t _reserved1[1023];
	volatile uint32_t SOPT2;
	uint32_t _reserved2;  // SOPT3?! not on K70?
	volatile uint32_t SOPT4;
	volatile uint32_t SOPT5;
	volatile uint32_t SOPT6;
	volatile uint32_t SOPT7;  // 0x8008
	uint32_t _reserved3[2];
	volatile uint32_t SDID;
	volatile uint32_t SCGC1;
	volatile uint32_t SCGC2;
	volatile uint32_t SCGC3;
	volatile uint32_t SCGC4;
	volatile uint32_t SCGC5;
	volatile uint32_t SCGC6;
	volatile uint32_t SCGC7;
	volatile uint32_t CLKDIV1;
	volatile uint32_t CLKDIV2;
	volatile uint32_t FCFG1;
	volatile uint32_t FCFG2;
	volatile uint32_t UID[4];  // H, MH, ML, L
	volatile uint32_t CLKDIV3;
	volatile uint32_t CLKDIV4;
	volatile uint32_t MCR;
};

template <typename T>
class NXP_SIM_K70_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;
		// FIXME - need do rcc_enums.h.j2 style hacking!
		template <typename Bus>
		void enable(Bus dev) const {
			sim::enable(*this, dev);
		}

		template <typename Bus>
		void disable(Bus dev) const {
			sim::disable(*this, dev);
		}
};
