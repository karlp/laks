#pragma once

#include <mmio/mmio.h>

struct NXP_PCR_KX_reg_t {
	volatile uint32_t PCR[32];
	volatile uint32_t GPCLR;
	volatile uint32_t GPCHR;
	uint32_t _reserved1[6];
	volatile uint32_t ISFR;
};

// struct NXP_GPIO_KX_reg_t {
// 	volatile uint32_t PDOR;
// 	volatile uint32_t PSOR;
// 	volatile uint32_t PCOR;
// 	volatile uint32_t PTOR;
// 	volatile uint32_t PDIR;
// 	volatile uint32_t PDDR;
// };

// FIXME - unhappy with this, too awkward to use
template <typename T>
class NXP_PCR_KX_t : public mmio_ptr<T> {
	public:
		using mmio_ptr<T>::ptr;
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

		void mux(uint32_t pin, MuxMode mode) const {
			ptr()->PCR[pin] = (ptr()->PCR[pin] & ~(0x7<<8)) | (mode & 0x7) << 8;
		}
};


// class NXP_GPIO_KX_t : public mmio_ptr<NXP_GPIO_KX_reg_t> {
// 	public:
// 		using mmio_ptr<NXP_GPIO_KX_t>::ptr;
		
// 		class Pin {
// 			private:
// 				const NXP_GPIO_KX_t& g;
			
// 			public:
// 				const int n;
// 				constexpr Pin(const NXP_GPIO_KX_t& gpio, const int pin) : g(gpio), n(pin) {}

// 				void set_out() {
// 					g->PDDR |= (1<<n);
// 				}
// 				void set_in() {
// 					g->PDDR &= ~(1<<n);
// 				}
				
// 				void on() {
// 					g->PSOR = 1 << n;
// 				}
				
// 				void off() {
// 					g->PCOR = 1 << n;
// 				}
				
// 				void set(bool value) {
// 					if(value) {
// 						on();
// 					} else {
// 						off();
// 					}
// 				}
				
// 				bool get() {
// 					return g->PDIR & (1 << n);
// 				}
				
// 				void toggle() {
// 					g->PTOR = (1<<n);
// 				}

// 		};
		
// };

