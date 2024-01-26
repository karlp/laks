#pragma once

#include <mmio/mmio.h>

struct NXP_RCM_K70_reg_t {
	volatile uint8_t SRS0;
	volatile uint8_t SRS1;
	uint8_t _reserved1[2];
	volatile uint8_t RPFC;
	volatile uint8_t RPFW;
	uint8_t _reserved2;
	volatile uint8_t MR;
};

template <typename T>
class NXP_RCM_K70_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;
		// void unlock() const {
		// 	ptr()->UNLOCK = 0xc520;
		// 	ptr()->UNLOCK = 0xd928;
		// }

		// void disable() const {
		// 	ptr()->STCTRLH &= ~(1<<0);
		// }
};
