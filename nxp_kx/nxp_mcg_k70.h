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
	// void unlock() const {
	// 	ptr()->UNLOCK = 0xc520;
	// 	ptr()->UNLOCK = 0xd928;
	// }

	// void disable() const {
	// 	ptr()->STCTRLH &= ~(1<<0);
	// }
};
