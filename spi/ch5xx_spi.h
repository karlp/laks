#pragma once

#include <mmio/mmio.h>

// This is used on, at least, CH5[678][789] and CH57[13]
// It appears to be used on all the 32bit MCUs, that are _not_
// CH32V, ie, the not the ones that are "stm32style"
// It is _not_ used on the 8051 CH559 and friends.
struct CH5xx_SPI_reg_t {
	volatile uint8_t CTRL_MOD;
	volatile uint8_t CTRL_CFG;
	volatile uint8_t INT_EN;
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
class CH5xx_SPI_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;
		uint8_t transfer_byte(uint8_t out = 0) {
			ptr()->BUFFER = out;

			while(!(ptr()->INT_FLAG & (1<<6))) {
			}

			return ptr()->BUFFER;
		}

		/// Starts a dma transfer, you should poll for completion.
		/// \param buf NOTE, this _must_ be in RAM! (hw limitation)
		/// \param len
		void send_block_dma(uint8_t *buf, uint16_t len) {
			ptr()->DMA_BEGIN = (uint32_t)buf;
			ptr()->DMA_END = (uint32_t)(buf + len);
			ptr()->TOTAL_COUNT = len;
			// Clear completion flags...
			ptr()->INT_FLAG = (1<<0) | (1<<3);
			// no interrupts, just poll for it..
			ptr()->CTRL_CFG |= (1<<0); // dma enable
		}
};
