#pragma once

#include <mmio/mmio.h>
#include <syscfg/syscfg.h>

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

	// Extremely naiive, no leap years, no time before 2020. just... basic go
	void init(int year, int month, int day, int hour, int min, int sec) const
	{
		// so, days are since 2020-1-1, and then I need a "2 seconds" count
		// and a "32k clock ticks" count.... yolo that shit right now.
		int net_years = year - 2020;
		int net_months = month - 1;
		int net_days = day - 1;
		int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		uint32_t sum_days = net_years * 365;
		for (auto i = 0; i < net_months; i++) {
			sum_days += mdays[i];
		}
		sum_days += net_days;
		int sum_secs = hour * 3600 + min * 60 + sec;
		int secs2 = sum_secs / 2;
		int ck32ticks = 0; // couldn't care less about this level of precision right now.
		uint32_t tt = (secs2 << 16 | ck32ticks);

		SYSCFG.unlock_safe();
		ptr()->TRIG = sum_days;
		ptr()->MODE_CTRL |= (1 << 7); // LOAD_HI
		SYSCFG.unlock_safe();
		ptr()->TRIG = tt;
		ptr()->MODE_CTRL |= (1 << 6); // LOAD_LO
		SYSCFG.lock_safe();
	}

	// Just read the lower portion and return a 32bit milleseconds counter...
	// Note, this is _expensive_ it's just to test sanity.
	int msecs() const {
		// make sure that seconds didn't roll over while we read the lower bits..
		int c32 = ptr()->CNT_32K;
		int s2 = ptr()->CNT_2S;
		int out = s2 * 2 * 1000;
		out += c32 * 1000 / 32768;
		return out;
	}
};