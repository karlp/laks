#pragma once

#include <mmio/mmio.h>

struct CH5xx_ADC_reg_v1_t {
	volatile uint8_t CHANNEL;
	volatile uint8_t CFG;
	volatile uint8_t CONVERT;
	volatile uint8_t TEMP;
	volatile uint16_t DATA;
	volatile uint8_t INT_FLAG;
	uint8_t _reserved1;
	/* unclear if this is an overlayed 32bit or what... */
	volatile uint8_t DMA_CTRLS;
	volatile uint8_t DMA_CTRLI;
	volatile uint8_t DMA_IF;
	volatile uint8_t DMA_AUTO_CYCLE;
	volatile uint16_t DMA_NOW;
	uint16_t _reserved3;
	volatile uint16_t DMA_BEGIN;
	uint16_t _reserved4;
	volatile uint16_t DMA_END;
};


class CH5xx_ADC_t : public mmio_ptr<CH5xx_ADC_reg_v1_t> {
	public:
		using mmio_ptr<CH5xx_ADC_reg_v1_t>::ptr;
};
