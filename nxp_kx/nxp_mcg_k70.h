#pragma once

#include <mmio/mmio.h>

struct NXP_MCG_K70_reg_t
{
	volatile uint8_t C1;
	volatile uint8_t C2;
	volatile uint8_t C3;
	volatile uint8_t C4;
	volatile uint8_t C5;
	volatile uint8_t C6;
	volatile uint8_t S;
	uint8_t _reserved1;
	volatile uint8_t SC;
	uint8_t _reserved2;
	volatile uint8_t ATCVH;
	volatile uint8_t ATCVL;
	volatile uint8_t C7;
	volatile uint8_t C8;
	uint8_t _reserved_c9;
	volatile uint8_t C10;
	volatile uint8_t C11;
	volatile uint8_t C12;
	volatile uint8_t S2;
};

template <typename T>
class NXP_MCG_K70_t : public mmio_ptr<T>
{
public:
	using mmio_ptr<T>::ptr;
	void set_range(int range) const
	{
		ptr()->C2 &= ~(0x3 << 4);
		ptr()->C2 |= ((range & 0x3) << 4);
	}
	void set_gain_high(bool on) const {
		if (on) {
			ptr()->C2 |= (1<<3);
		} else {
			ptr()->C2 &= ~(1<<3);
		}
	}
	void set_ext_ref_osc(bool on) const {
		if (on) {
			ptr()->C2 |= (1<<2);
		} else {
			ptr()->C2 &= ~(1<<2);
		}
	}
	bool plls_is_pll(void) const {
		return ptr()->S & (1<<5);
	}
	bool pll_is_locked(void) const {
		return ptr()->S & (1<<6);
	}

	void config_pll(int prdiv, int vdiv, int enable_mode) const
	{
		// off, but configure prdiv
		ptr()->C5 = prdiv & 0x1f;
		ptr()->C6 &= ~(0x1f);
		ptr()->C6 |= vdiv & 0x1f;
		ptr()->C6 |= (1<<6); // turn it on again
		while (!pll_is_locked()) {
			;
		}
	}

	void clock_source(int source) const
	{
		ptr()->C1 &= ~(0x3<<6);
		ptr()->C1 |= (source & 0x3) << 6;
	}

	int clock_source(void) const {
		return (ptr()->S >> 2) & 0x3;
	}
};
