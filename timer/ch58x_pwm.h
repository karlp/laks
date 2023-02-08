#pragma once

#include <mmio/mmio.h>

/// For... reasons, this is PWM4..11.  I suspect 0..3 are
// the ones you're meant to get from the timer system?

struct CH58x_PWM_reg_t {
	volatile uint8_t OUT_EN;
	volatile uint8_t POLARITY;
	volatile uint8_t CONFIG;
	/// Fpwm = Fsys/CLOCK_DIV;
	volatile uint8_t CLOCK_DIV;
	union {
		struct {
			volatile uint32_t DATA[2];
		};
		struct {
			volatile uint8_t DATA8[8];
		};
	};
	volatile uint8_t INT_CTRL;
};

template <typename T>
class CH58x_PWM_t : public mmio_ptr<T> {
    public:
        using mmio_ptr<T>::ptr;
	void enable(uint8_t channel) {
		ptr()->OUT_EN |= (1<< (channel - 4));
	}

	void set(uint8_t channel, uint8_t value) {
		ptr()->DATA8[channel - 4] = value;
	}
};

