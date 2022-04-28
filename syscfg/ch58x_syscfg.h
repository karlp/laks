#pragma once

#include <mmio/mmio.h>

struct CH58x_SYSCFG_reg_t {
	volatile uint8_t SAFE_ACCESS_SIG;
	volatile uint8_t CHIP_ID;
	volatile uint8_t SAFE_ACCESS_ID;
	volatile uint8_t WDOG_COUNT;
	union {
		volatile uint8_t RESET_STATUS;
		volatile uint8_t GLOB_ROM_CFG;
	};
	volatile uint8_t GLOB_CFG_INFO;
	volatile uint8_t RST_WDOG_CTRL;
	volatile uint8_t GLOB_RESET_KEEP;
};

template <typename T>
class CH58x_SYSCFG_t : public mmio_ptr<T> {
    public:
        using mmio_ptr<T>::ptr;

	/**
	 * Unlocks RWA/WA registers for 16 sys clocks!
	 */
	void unlock_safe(void) const {
		ptr()->SAFE_ACCESS_SIG = 0x57;
		ptr()->SAFE_ACCESS_SIG = 0xA8;
		asm volatile("nop");
		asm volatile("nop");
	}

	void lock_safe(void) const {
		ptr()->SAFE_ACCESS_SIG = 0;
	}
};
