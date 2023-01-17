#pragma once

#include <mmio/mmio.h>

// Ignore v1/v2 differences, it's only in fields
// and access width to the DR register.
struct STM32_SPI_reg_t {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	union {
		volatile uint32_t DR;
		volatile uint8_t DR8;
	};
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
};

template <typename T>
class STM32_SPI_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;

		// yes, using the lower8 will do the right thing on both
		// v1/v2 spi peripherals!
		uint8_t transfer_byte(uint8_t out = 0) {
			ptr()->DR8 = out;
			
			while(!(ptr()->SR & 0x01)) {
			}
			
			return ptr()->DR8;
		}
};
