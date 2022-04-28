#pragma once

#include <stdint.h>
#include <mmio/mmio.h>

// FIXME - the data/control overlay here is insane.
struct CH58x_FLASH_reg_t {
	volatile uint32_t DATA;
	union {
		struct {
			volatile uint32_t CONTROL;
		};
		struct {
			volatile uint8_t DATA8;
			uint8_t _reserved1;
			volatile uint8_t CONTROL8;
			volatile uint8_t CFG;
		};
	};
};


template <typename T>
class CH58x_FLASH_t : public mmio_ptr<T> {
    public:
        using mmio_ptr<T>::ptr;
};
