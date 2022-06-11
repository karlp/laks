#pragma once

#include <mmio/mmio.h>

struct CH58x_RTC_reg_t {
	volatile uint8_t FLAG_CTRL; // 0x30
	volatile uint8_t MODE_CTRL; // 0x31
	uint8_t _reserved2[2];
	volatile uint32_t TRIG; // 0x34
	volatile uint16_t CNT_32K; // 0x38
	volatile uint16_t CNT_2S; // 0x3a
	volatile uint32_t CNT_DAY; // 0x3c
};

template <typename T>
class CH58x_RTC_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;
};

