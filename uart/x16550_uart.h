#pragma once

#include <mmio/mmio.h>

#include <type_traits>

struct x16550_UART_reg_t {
	volatile uint8_t MCR;
	volatile uint8_t IER;
	volatile uint8_t FCR;
	volatile uint8_t LCR;
	volatile uint8_t IIR;
	volatile uint8_t LSR;
	volatile uint8_t MSR;
	uint8_t _reserved1;
	union {
		volatile uint8_t RBR;
		volatile uint8_t THR;
	};
	uint8_t _reserved2;
	volatile uint8_t RFC;
	volatile uint8_t TFC;
	volatile uint16_t DL;
	volatile uint8_t DIV;
	volatile uint8_t ADR;
};


template <typename T>
class x16550_UART_t : public mmio_ptr<T> {
    public:
        using mmio_ptr<T>::ptr;

	enum IIRFlag {
		NoInterrupt = 1,
		BusAddressMatch = (7<<1),
		LineStatus = (3<<1),
		RxData = (2<<1),
		RxTimeOut = (6<<1),
		TxEmpty = (1<<1),
		ModemChange = 0,
	};

	/**
	 * Basic init for plain simply full duplex, fifo mode.
	 * @param sysclk required to calculate baud
	 * @param baud desired baud
	 * @param rx_fifo either 0, 1, 2,or 3 for 1,2,4,7 byte rx fifo
	 * @param lcr the full LCR register, this is parity/wordsize stuff default is 8n1
	 */
	void init(int sysclk, int baud, uint8_t rx_fifo = 0x3, uint8_t lcr = 0x3) const
	{
		// Flush and enable fifos. (ie, 16550 mode, not 16450 mode)
		ptr()->FCR = (rx_fifo << 6) | 0x7;
		ptr()->LCR = lcr; // default is 8n1
		ptr()->IER = (1 << 6); // enable TXD output
		ptr()->DIV = 1; // "standard" prescaler

		auto dl = sysclk * 2 / 1 / 16 / baud;
		ptr()->DL = dl;
		// hard enabling irqs in the _periph_ is ok right?
		ptr()->IER |= (1 << 0); // RECV_RDY irqs
		ptr()->MCR |= (1 << 3); // peripheral IRQ enable..
	}

	bool txe() const {
		return ptr()->LSR & (1 << 5);
	}

	bool rxne() const {
		return ptr()->LSR & (1 << 0);
	}

	void write(uint8_t data) const {
		ptr()->THR = data;
	}

	void write_blocking(uint8_t data) const {
		while(!txe());
		write(data);
	}

	uint8_t read() {
		return ptr()->RBR;
	}

	uint8_t read_blocking() const {
		while(!rxne());
		return read();
	}

};
