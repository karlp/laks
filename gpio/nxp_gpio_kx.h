#pragma once

#include <mmio/mmio.h>

struct NXP_PCR_KX_reg_t {
	volatile uint32_t PCR[32];
	volatile uint32_t GPCLR;
	volatile uint32_t GPCHR;
	uint32_t _reserved1[6];
	volatile uint32_t ISFR;
};

struct NXP_GPIO_KX_reg_t {
	volatile uint32_t PDOR;
	volatile uint32_t PSOR;
	volatile uint32_t PCOR;
	volatile uint32_t PTOR;
	volatile uint32_t PDIR;
	volatile uint32_t PDDR;
};

// FIXME - unhappy with this, too awkward to use
// Ideally I want to link the PCR from the GPIO...
class NXP_PCR_KX_t : public mmio_ptr<NXP_PCR_KX_reg_t> {
	public:
		using mmio_ptr<NXP_PCR_KX_reg_t>::ptr;
		enum MuxMode {
			Disabled = 0,
			Alt1_GPIO = 1,
			Alt2,
			Alt3,
			Alt4,
			Alt5,
			Alt6,
			Alt7,
		};

		class PinMux {
			private:
				const NXP_PCR_KX_t& p;

			public:
				const int n;
				constexpr PinMux(const NXP_PCR_KX_t& p, const int pin) : p(p), n(pin) {}

				void mux(MuxMode mode) {
					p->PCR[n] = (p->PCR[n] & ~(0x7<<8)) | (mode & 0x7) << 8;
				}

				// Could also have an enum for up/down/off?
				void pull(bool enable, bool up) {
					p->PCR[n] = (p->PCR[n] & ~(3)) | (enable ? 2 : 0) | (up ? 1 : 0);
				}
		};

		constexpr PinMux operator[](int pin) const {
			return PinMux(*this, pin);
		}

};


class NXP_GPIO_KX_t : public mmio_ptr<NXP_GPIO_KX_reg_t> {
	public:
		using mmio_ptr<NXP_GPIO_KX_reg_t>::ptr;

		class Pin {
			private:
				const NXP_GPIO_KX_t& g;

			public:
				const int n;
				constexpr Pin(const NXP_GPIO_KX_t& gpio, const int pin) : g(gpio), n(pin) {}

				void set_out() {
					g->PDDR |= (1<<n);
				}
				void set_in() {
					g->PDDR &= ~(1<<n);
				}

				void on() {
					g->PSOR = 1 << n;
				}

				void off() {
					g->PCOR = 1 << n;
				}

				void set(bool value) {
					if(value) {
						on();
					} else {
						off();
					}
				}

				bool get() {
					return g->PDIR & (1 << n);
				}

				void toggle() {
					g->PTOR = (1<<n);
				}

		};

		class PinArray {
			private:
				const NXP_GPIO_KX_t& g;
				int f;
				int l;

				// constexpr uint32_t mask1() {
				// 	return ((2 << l) - 1) ^ ((1 << f) - 1);
				// }

				// constexpr uint32_t mask2() {
				// 	return ((4 << (l * 2)) - 1) ^ ((1 << (f * 2)) - 1);
				// }

			public:
				constexpr PinArray(const NXP_GPIO_KX_t& gpio, int first, int last) : g(gpio), f(first), l(last) {}

				// void set(uint16_t value) {
				// 	value <<= f;
				// 	g->BSRR = ((~value & mask1()) << 16) | (value & mask1());
				// }

				// uint16_t get() {
				// 	return (g->IDR & mask1()) >> f;
				// }
		};

		constexpr Pin operator[](int pin) const {
			return Pin(*this, pin);
		}

		constexpr PinArray array(int first, int last) const {
			return PinArray(*this, first, last);
		}

};

