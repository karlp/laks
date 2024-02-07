#pragma once

#include <mmio/mmio.h>

#include <type_traits>

// Per NXP: "Only byte accesses are supported."

struct NXP_UART_reg_kxv1_t
{
	volatile uint8_t BDH;
	volatile uint8_t BDL;
	volatile uint8_t C1;
	volatile uint8_t C2;
	volatile uint8_t S1;
	volatile uint8_t S2;
	volatile uint8_t C3;
	volatile uint8_t D;
	volatile uint8_t MA1;
	volatile uint8_t MA2;
	volatile uint8_t C4;
	volatile uint8_t C5;
	volatile uint8_t ED;
	volatile uint8_t MODEM;
	volatile uint8_t IR;
	uint8_t _reserved1;
	volatile uint8_t PFIFO;
	volatile uint8_t CFIFO;
	volatile uint8_t SFIFO;
	volatile uint8_t TWFIFO;
	volatile uint8_t TCFIFO;
	volatile uint8_t RWFIFO;
	volatile uint8_t RCFIFO;
	uint8_t _reserved2;
	/* ISO7816 chunk */
	volatile uint8_t C7816;
	volatile uint8_t IE7816;
	volatile uint8_t IS7816;
	volatile uint8_t WP7816; // Also WP7816T1, alias?
	volatile uint8_t WN7816;
	volatile uint8_t WF7816;
	volatile uint8_t ET7816;
	volatile uint8_t TL7816;
	uint8_t _reserved3;
	/* CEA709 chunk */
	volatile uint8_t C6;
	volatile uint8_t PCTH;
	volatile uint8_t PCTL;
	volatile uint8_t B1T;
	volatile uint8_t SDTH;
	volatile uint8_t SDTL;
	volatile uint8_t PRE;
	volatile uint8_t TPL;
	volatile uint8_t IE;
	volatile uint8_t WB;
	volatile uint8_t S3;
	volatile uint8_t S4;
	volatile uint8_t RPL;
	volatile uint8_t RPREL;
	volatile uint8_t CPW;
	volatile uint8_t RIDT;
	volatile uint8_t TIDT;
};

struct NXP_UART_reg_lpv1_t
{
	volatile uint32_t BAUD;
	volatile uint32_t STAT;
	volatile uint32_t CTRL;
	volatile uint32_t DATA;
	volatile uint32_t MATCH;
	volatile uint32_t MODIR;
	volatile uint32_t ICR;
	volatile uint32_t RDR;
	volatile uint32_t TDR;
};

template <typename T>
class NXP_UART_t : public mmio_ptr<T>
{
public:
	using mmio_ptr<T>::ptr;

	bool txe() const
	{
		return ptr()->S2 & (1 << 7);
	}

	bool rxne() const
	{
		return ptr()->S2 & (1 << 5);
	}

	/** FIXME: if you want 9bit mode, you need to get it from ->C3[7]! */
	uint8_t read() const
	{
		return ptr()->D;
	}

	/** FIXME: if you want 9bit mode, you need to write it to C3[6]*/
	void write(uint8_t data) const
	{
		ptr()->D = data;
	}

	uint8_t read_blocking() const
	{
		while (!rxne())
			;
		return read();
	}

	void write_blocking(uint8_t data) const
	{
		while (!txe())
			;
		write(data);
	}

	void baud(uint16_t baud) const
	{
		if constexpr (std::is_same_v<T, NXP_UART_KX_reg_lpv1_t>)
		{
			ptr()->BAUD &= ~(0x1fff);
			ptr()->BAUD |= (baud & 0x1fff);
		}
		else
		{
			ptr()->BDH &= ~(0x1f);
			ptr()->BDH |= (baud >> 8);
			ptr()->BDL = (baud & 0xff);
		}
	}
};
