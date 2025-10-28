#pragma once

#include <mmio/mmio.h>

struct NXP_OSC_K70_reg_t
{
	volatile uint8_t CR;
};

template <typename T>
class NXP_OSC_K70_t : public mmio_ptr<T>
{
public:
	using mmio_ptr<T>::ptr;

	void set_cap_load(uint8_t load) const
	{
		ptr()->CR &= ~(0xf << 0);
		ptr()->CR |= load;
	}

	/**
	 * Manage the External Reference Enable (OSCERCLK) (ERCLKEN bit)
	 */
	void enable_ext_ref(bool on) const
	{
		if (on) {
			ptr()->CR |= (1<<7);
		} else {
			ptr()->CR &= ~(1<<7);
		}
	}
};
