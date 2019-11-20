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
// rvalues???????
// wybadac teren - Piotrus


//liczy n-tą liczbę fibo
unsigned long long fib(unsigned int n) {
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
void Fibo::set_digit(size_t fib_index, bool value) {
    digits[fib_index - 2] = value == ONE;
}

//konstruktor bezparametrowy
Fibo::Fibo() : digits(1, ZERO){};

//konstruktor ze Stringa
Fibo::Fibo(const std::string &s) {
	assert(s[0] == '1');
    for (auto it = s.rbegin(); it != s.rend(); it++) {
    	assert(*it == '0' || *it == '1');
        digits.push_back(*it == '1');
    }
    normalize();
}

Fibo::Fibo(const char* c) : Fibo(std::string(c)){
	assert(c != nullptr);
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



//główny konstructor
Fibo::Fibo(unsigned long long n) {
    if (n == 0) {
        digits.push_back(ZERO);
        return;
    }

    size_t i = greatest_fitting_fib(n);
    digits.resize(i - 1);
    for (; i >= 2; i--) {
        if (fib(i) <= n) {
            set_digit(i, ONE);
            n -= fib(i);
        }
    }
}

Fibo::Fibo(int n) : Fibo((unsigned long long) n){
	assert(n >= 0);
}

Fibo::Fibo(unsigned int n) : Fibo((unsigned long long) n){}

Fibo::Fibo(long n) : Fibo((unsigned long long) n){
	assert(n >= 0);
}

void Fibo::add_one_at_position(size_t i) {
    digits.push_back(ZERO);

    size_t add_at = i;
    while (add_at >= 0) {
        if (digits[add_at] == 1) {
            digits[add_at + 1] = ONE;
            digits[add_at] = ZERO;
            if(add_at < 2){
				break;
            } else{
				add_at -= 2;
			}
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
    static const Fibo one("1");
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



//TODO pokombinowc czy napewno w ten sposob moze jakies Rvalue
const Fibo operator+(Fibo a, const Fibo &b) {
	return a += b;
}

const Fibo operator+(unsigned long long a , const Fibo &b) {
	return Fibo(a) += b;
}

Fibo& Fibo::operator=(Fibo&& other) noexcept {
    digits = move(other.digits);
    return *this;
}

Fibo& Fibo::operator=(const Fibo& that) = default;



size_t Fibo::length() const {
    return digits.size();
}

Fibo& Fibo::operator<<=(const unsigned n) {
    Digits zeroes(n);
    zeroes.insert(zeroes.end(), make_move_iterator(digits.begin()), make_move_iterator(digits.end()));
    digits = move(zeroes);
    return *this;
}

Fibo Fibo::operator<<(unsigned n) const {
    return Fibo(*this) <<= n;
}

Fibo& Fibo::operator&=(const Fibo &other) {
    size_t length = min(this->length(), other.length());
    for (size_t i = 0; i < length; i++) {
        digits[i] = digits[i] && other.digits[i];
    }
    normalize();
    return *this;
}

Fibo Fibo::operator&(const Fibo &other) const {
    return Fibo(*this) &= other;
}

//TODO NORMALIZUJ WSZEDZIE PRZ OPERATORACH
Fibo& Fibo::operator|=(const Fibo &other) {
    size_t length = min(this->length(), other.length());
    for (size_t i = 0; i < length; i++) {
        digits[i] = digits[i] || other.digits[i];
    }
    return *this;
}

Fibo Fibo::operator|(const Fibo &other) const {
    return Fibo(*this) |= other;
}

Fibo& Fibo::operator^=(const Fibo &other) {
    size_t length = min(this->length(), other.length());
    for (size_t i = 0; i < length; i++) {
        digits[i] = digits[i] ^ other.digits[i];
    }
    normalize();
    return *this;
}

Fibo Fibo::operator^(const Fibo &other) const {
    return Fibo(*this) ^= other;
}

bool Fibo::operator==(const Fibo &other) const {
    if (length() != other.length()) {
        return false;
    }

    for (size_t i = 0; i < length(); i++) {
        if(digits[i] != other.digits[i]){
			return false;
        }
    }
    return true;
}

bool Fibo::operator!=(const Fibo &other) const {
    return !(*this == other);
}

bool Fibo::operator<(const Fibo &other) const {
    if (length() > other.length()) {
        return false;
    }

    if (length() < other.length()) {
        return true;
    }

    size_t i = length() - 1;
    for (auto it = digits.rbegin(); it != digits.rend(); it++) {
        if (*it && !other.digits[i]) {
            return false;
        }
        if (!(*it) && other.digits[i]) {
            return true;
        }
        i--;
    }
    return false;
}

bool Fibo::operator>(const Fibo &other) const {
    return (*this != other) && !(*this < other);
}

bool Fibo::operator<=(const Fibo &other) const {
    return !(*this > other);
}

bool Fibo::operator>=(const Fibo &other) const {
    return !(*this < other);
}

ostream& operator<<(ostream& os, const Fibo& fibo){
	for(auto it = fibo.digits.rbegin(); it != fibo.digits.rend(); it++){
		if(*it){
			std::cout << "1";
		}else{
			std::cout << "0";
		}
	}
	std::cout << std::endl;
	return os;
}




