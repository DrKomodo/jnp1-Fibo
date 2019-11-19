#include <iostream>
#include "fibo.h"
#include <vector>
#include <cassert>


using Digit = bool;
using Digits = std::vector<Digit>;

const bool ZERO = false;
const bool ONE = true;

using namespace std;


//czy mi dziala
// Pytania:
//czy argument do konstruktora ma byc przez referencje?
//co ma byc w .cpp a co w .h?
//jak inicjowac member objects kiedy argumenty ich oknstruktorow trzeba najpierw obliczyć tzn czy da sie uzyc
//initializer list?
// czy mamy uzywac unsigned? problem taki, ze wtedy warunki w petlach typu >= 0 nie ddzialaja


// Do zrobienia:
//
// short int long zeby dizlalo - Piotrus :((((
// niezmieniajace sie obiekty One itp.
// rvalues???????
// operacje porownywania przesuniecie bitowe reszta operatorow
// wybadac teren - Piotrus
// podzielic elegancko na moduly (latwe)


//liczy n-tą liczbę fibo
unsigned long long fib(unsigned long long int n) {
	static std::vector<unsigned long long> fib_numbers(2);
	fib_numbers[0] = 0;
	fib_numbers[1] = 1;

	if (n <= 0) {
		return 0;
	}

	if (n >= fib_numbers.size()) {
		fib_numbers.resize(n + 1);
	}

	if (fib_numbers[n] != 0) {
		return fib_numbers[n];
	}

	return fib_numbers[n] = fib(n - 1) + fib(n - 2);
}

//ustawia na indeksie
//TODO czemu short nie bool?
void Fibo::set_digit(size_t fib_index, short value) {
	digits[fib_index - 2] = value == 1;
}


void Fibo:: print() const{ //funkcja robocza
	for(auto it = digits.rbegin(); it != digits.rend(); it++){
		if(*it){
			std::cout << "1";
		}else{
			std::cout << "0";
		}
	}
	std::cout << std::endl;
}

//chyba lepiej, inicjalizuje digits z jednym elementem ZERO
//konstruktor bezparametrowy
Fibo::Fibo() : digits(1, ZERO){};

//TODO Assertion dla nie zer, co gd
//konstruktor ze Stringa
Fibo:: Fibo(const std::string &s) { //co zrobic gdy s nie jest ciagiem zer i jedynek? (na razie zakladam ze jest)
	for (auto it = s.rbegin(); it != s.rend(); it++) {
		digits.push_back(*it == '1');
	}
	normalize();
}

//copy constructor
Fibo::Fibo(const Fibo& other) = default;

// move constructor
Fibo::Fibo(Fibo&& other) noexcept : digits(move(other.digits)){}


namespace {
	bool iterate_until_repetition(const Digits &d, size_t &current_index) {
		Digit current_value = d[current_index];
		while (current_index > 0) {
			if (d[current_index - 1] == current_value) {
				current_index--;
				return true;
			} else {
				current_index--;
				current_value = d[current_index];
			}
		}
		return false;
	}

	void handle_doubled_ones(Digits &d, size_t &current_index, size_t &free_slot) {
		d[free_slot] = ONE;
		for (size_t i = free_slot; i-- > current_index;) {
			d[i] = ZERO;
		}
		free_slot = current_index;
	}
}

void Fibo::normalize() {
	digits.push_back(ZERO);
	size_t free_slot = digits.size() - 1;
	size_t current_index = digits.size() - 1;
	while (iterate_until_repetition(digits, current_index)) {
		if (digits[current_index] == 0) {
			free_slot = current_index;
		} else {
			handle_doubled_ones(digits, current_index, free_slot);
		}
	}

	while (digits.back() == 0 && digits.size() > 1) {
		digits.pop_back();
	}
}

namespace {
	size_t greatest_fitting_fib(unsigned long long n) {
		size_t i = 0;
		while (fib(i + 1) <= n) {
			i++;
		}
		return i;
	}
}

Fibo::Fibo(long long int a) {
	assert(a >= 0);
	unsigned long long n = a; //konwersja
	if (n == 0) {
		digits.push_back(ZERO);
		return;
	}

	size_t i = greatest_fitting_fib(n);
	digits.resize(i - 1);
	for (; i >= 2; i--) {
		if (fib(i) <= n) {
			set_digit(i, 1);
			n -= fib(i);
		}
	}
}


void Fibo::add_one_at_position(size_t i) {
	digits.push_back(ZERO);

	int add_at = i;
	while (add_at >= 0) {
		if (digits[add_at] == 1) {
			digits[add_at + 1] = ONE;
			digits[add_at] = ZERO;
			add_at -= 2;
		} else {
			digits[add_at] = ONE;
			break;
		}
	}
	normalize();
}

const Fibo& Zero() {
	static const Fibo zero;
	return zero;
}

const Fibo& One() {
	static const Fibo one(1);
	return one;
}

Fibo& Fibo::operator+=(const Fibo &other) {
	if (this == &other) {
		return *this;
	}

	if (other.digits.size() > digits.size()) {
		digits.resize(other.digits.size());
	}

	for (size_t i = 0; i < other.digits.size(); i++) {
		if (other.digits[i] == 1) {
			add_one_at_position(i);
		}
	}

	return *this;
}

Fibo& Fibo::operator=(Fibo&& other) noexcept {
	digits = move(other.digits);
	return *this;
}

Fibo& Fibo::operator=(const Fibo& that) = default;

//TODO pokombinowc czy napewno w ten sposob moze jakies Rvalue
Fibo Fibo::operator+(const Fibo &other) const {
	return Fibo(*this) += other;
}

size_t Fibo::length(){
	return digits.size();
}


