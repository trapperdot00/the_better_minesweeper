#ifndef ANSICOLOR_H
#define ANSICOLOR_H

#include <string>

class AnsiColor {
public:
	std::string wrap(const std::string& text) const {
		return begin() + text + end();
	}

	std::string begin() const { return _begin; }
	std::string end() const { return "\e[0m"; }

	static const AnsiColor black;
	static const AnsiColor red;
	static const AnsiColor green;
	static const AnsiColor yellow;
	static const AnsiColor blue;
	static const AnsiColor purple;
	static const AnsiColor cyan;
	static const AnsiColor white;
private:
	explicit AnsiColor(const std::string& begin) :
		_begin{begin}
	{}
private:
	std::string _begin;
};

#endif
