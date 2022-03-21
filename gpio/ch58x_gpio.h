#pragma once

#include <mmio/mmio.h>

struct CH58x_GPIO_port_reg_t {
	volatile uint32_t DIR;
	volatile uint32_t PIN;
	volatile uint32_t OUT;
	volatile uint32_t CLR;
	volatile uint32_t PU;
	volatile uint32_t PD_DRV;
	uint32_t _reserved1[2];
};

struct CH58x_GPIO_reg_t {
	volatile uint16_t ALTERNATE;
	volatile uint16_t ANALOG_IE;
	uint16_t _reserved1[58]; // 0x4000101b..0x4000108f
	volatile uint16_t INT_EN[2];
	volatile uint16_t INT_MODE[2];
	uint16_t _reserved2[2];
	volatile uint16_t INT_IF[2];
	struct CH58x_GPIO_port_reg_t port[2];
};

class CH58x_GPIO_t : public mmio_ptr<CH58x_GPIO_reg_t> {
	public:
		using mmio_ptr<CH58x_GPIO_reg_t>::ptr;

		class Pin {
			private:
				const CH58x_GPIO_t& g;

			public:
				const int port;
				const int n;
				constexpr Pin(const CH58x_GPIO_t& gpio, const int port, const int pin) : g(gpio), port(port), n(pin) {}

				enum Mode {
					Input = 0,
					Output = 1,
				};

				void set_mode(Mode m) {
					if (m == Mode::Input) {
						g->port[port].DIR &= ~(1<<n);
					} else {
						g->port[port].DIR |= (1<<n);
					}
				}

				void on() {
					g->port[port].OUT = 1 << n;
				}

				void off() {
					g->port[port].CLR = 1 << n;
				}

				void set(bool value) {
					if(value) {
						on();
					} else {
						off();
					}
				}

				bool get() {
					return g->port[port].PIN & (1 << n);
				}

				void toggle() {
					set(!(get()));
				}

		};


		constexpr Pin operator[](int pin) const {
			int port = (pin >> 8) & 0xff;
			pin &= 0xff;
			return Pin(*this, port, pin);
		}

};
