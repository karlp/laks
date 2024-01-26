#pragma once

#include <mmio/mmio.h>

struct NXP_WDOG_K70_reg_t {
	volatile uint16_t STCTRLH;
	volatile uint16_t STCTRLL;
	volatile uint16_t TOVALH;
	volatile uint16_t TOVALL;
	volatile uint16_t WINH;
	volatile uint16_t WINL;
	volatile uint16_t REFRESH;
	volatile uint16_t UNLOCK;
	volatile uint16_t TMROUTH;
	volatile uint16_t TMROUTL;
	volatile uint16_t RSTCNT;
	volatile uint16_t PRESC;

};

template <typename T>
class NXP_WDOG_K70_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;
		void unlock() const {
			ptr()->UNLOCK = 0xc520;
			ptr()->UNLOCK = 0xd928;
		}

		void disable() const {
			ptr()->STCTRLH &= ~(1<<0);
		}
};
