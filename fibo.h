#ifndef JNP1_FIBO_FIBO_H
#define JNP1_FIBO_FIBO_H

#include <vector>

using Digit = bool;
using Digits = std::vector<Digit>;


class Fibo {

public:
	void print() const;
	Fibo();
	Fibo(const Fibo& other);
	Fibo(Fibo&& other) noexcept; //tak podpowiada z tym no except
	explicit Fibo(const std::string &s);
	Fibo(long long int n);
	//chyba inne typy: char, int, unsigned same sie skonwertuja do tego
	//TODO nie moze dzialac dla char... ehhh trzeba zmieniac

	Fibo& operator+=(const Fibo &other);
	Fibo& operator=(Fibo&& that) noexcept; //move
	Fibo&operator=(const Fibo& other);
	Fibo operator+(const Fibo& other) const;

	size_t length();

private:
	Digits digits;
	void normalize();
	void set_digit(size_t fib_index, short value);
	void add_one_at_position(size_t i);
};
static const Fibo& Zero();
static const Fibo& One();


#endif
