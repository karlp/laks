#pragma once

#include <mmio/mmio.h>

struct CH58x_GPTIMER_reg_t {
	// TODO
};

template <typename T>
class CH58x_GPTIMER_t : public mmio_ptr<T> {
    public:
        using mmio_ptr<T>::ptr;
};

