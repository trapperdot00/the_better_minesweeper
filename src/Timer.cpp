#include "Timer.h"

#include <stdexcept>
#include <format>
using namespace std::chrono;

auto Timer::start() -> void {
	if (_state != State::init) {
		throw std::logic_error{"timer has invalid state"};
	}
	_start = steady_clock::now();
	_state = State::started;
}

auto Timer::end() -> void {
	if (_state != State::started) {
		throw std::logic_error{"timer is not started"};
	}
	_end = steady_clock::now();
	_state = State::stopped;
}

auto Timer::reset() -> void {
	_state = State::init;
}

auto Timer::elapsed() const -> nanoseconds {
	if (_state != State::stopped) {
		throw std::logic_error{"timer is not stopped"};
	}
	return _end - _start;
}

auto Timer::rep() const -> std::string {
	if (_state != State::stopped) {
		throw std::logic_error{"timer not stopped"};
	}
	auto elapsed_min = duration_cast<minutes>(elapsed()).count();
	auto elapsed_sec = duration_cast<seconds>(elapsed() % minutes{1}).count();
	auto elapsed_msec = duration_cast<milliseconds>(elapsed() % seconds{1}).count();
	return std::format("{:0>2}:{:0>2}.{:0>3}", elapsed_min, elapsed_sec, elapsed_msec);
}
