#pragma once

#include <mmio/mmio.h>

struct NXP_MPU_KX_reg_t
{
	volatile uint32_t CESR;
	// not even close to complete!
};

template <typename T>
class NXP_MPU_KX_t : public mmio_ptr<T>
{
public:
	using mmio_ptr<T>::ptr;
	void disable() const
	{
		ptr()->CESR &= ~(1 << 0);
	}
};
