#pragma once

#include <mmio/mmio.h>

struct CH58x_SPI_reg_t {
	volatile uint8_t CTRL_MOD;
	volatile uint8_t CTRL_CFG;
	volatile uint8_t INTER_EN;
	union {
		volatile uint8_t CLOCK_DIV;
		volatile uint8_t PERIPH_PRE;
	};
	volatile uint8_t BUFFER;
	volatile uint8_t RUN_FLAG;
	volatile uint8_t INT_FLAG;
	volatile uint8_t FIFO_COUNT;
	uint8_t _reserved1[4];
	volatile uint16_t TOTAL_COUNT;
	uint16_t _reserved2;
	volatile uint8_t FIFO;
	uint8_t _reserved3[3];
	volatile uint8_t FIFO_COUNT1; // Explicit duplicate?
	// not all instances have DMA
	volatile uint16_t DMA_NOW;
	uint16_t _reserved4;
	volatile uint16_t DMA_BEGIN;
	uint16_t _reserved5;
	volatile uint16_t DMA_END;
};

template <typename T>
class CH58x_SPI_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;
		uint8_t transfer_byte(uint8_t out = 0) {
			ptr()->BUFFER = out;

			while(!(ptr()->INT_FLAG & (1<<6))) {
			}

			return ptr()->BUFFER;
		}
};
