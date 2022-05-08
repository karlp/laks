#pragma once

#include <mmio/mmio.h>

struct WCH_SYSTICK_reg_v4_t {
	volatile uint32_t CTLR;
	volatile uint32_t SR;
	volatile uint64_t CNT;
	volatile uint64_t CMP;
};

template <typename T>
class WCH_SYSTICK_t : public mmio_ptr<T> {
    public:
        using mmio_ptr<T>::ptr;
};

