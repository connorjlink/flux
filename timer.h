#ifndef FLUX_TIMER_H
#define FLUX_TIMER_H

// timer.h
// (c) 2025 Connor J. Link. All Rights Reserved.

namespace fx
{
	class Timer
	{
	public:
		Timer() noexcept;

	public:
		void reset() noexcept;

	public:
		float seconds() const noexcept;
		float milliseconds() const noexcept;
		float nanoseconds() const noexcept;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> _start;
	};

	class AutoTimer
	{
	public:
		AutoTimer(const std::string&) noexcept;
		~AutoTimer() noexcept;

	private:
		std::string _name;
		Timer _timer;
	};
}

#endif
