#ifndef JNP1_FIBO_FIBO_H
#define JNP1_FIBO_FIBO_H

#include <vector>

using Digit = bool;
using Digits = std::vector<Digit>;


class Fibo {

	Digits digits;
	void normalize();
	void set_digit(int fib_index, short value);
	void add_one_at_position(unsigned int i);

public:
	void print();
	Fibo();
	explicit Fibo(const std::string &s);
	explicit Fibo(unsigned long n);

	Fibo &operator+=(const Fibo &other);
};


#endif
