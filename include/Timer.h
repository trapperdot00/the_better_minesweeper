#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

class Timer {
public:
	auto start() -> void;
	auto end() -> void;
	auto reset() -> void;

	auto elapsed() const -> std::chrono::nanoseconds;

	auto rep() const -> std::string;
private:
	enum class State {
		init,
		started,
		stopped
	} _state = State::init;
	std::chrono::time_point<std::chrono::steady_clock> _start;
	std::chrono::time_point<std::chrono::steady_clock> _end;
};

#endif
