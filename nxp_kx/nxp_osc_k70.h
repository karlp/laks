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
};
