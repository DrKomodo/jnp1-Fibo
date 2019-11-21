#include <iostream>
#include "fibo.h"
#include <vector>
#include <cassert>

using Digit = bool;
using Digits = std::vector<Digit>;

const Digit ZERO = false;
const Digit ONE = true;

namespace{
	//liczy n-tą liczbę fibonaciego
	unsigned long long fib_n(unsigned int n){
		static std::vector<unsigned long long> fib_numbers(2);
		fib_numbers[0] = 0;
		fib_numbers[1] = 1;

		if(n <= 0){
			return 0;
		}

		if(n >= fib_numbers.size()){
			fib_numbers.resize(n + 1);
		}

		if(fib_numbers[n] != 0){
			return fib_numbers[n];
		}

		return fib_numbers[n] = fib_n(n - 1) + fib_n(n - 2);
	}
}

//ustawia na indeksie
void Fibo::set_digit(size_t fib_index, Digit value){
	digits[fib_index - 2] = (value == ONE);
}

//konstruktor bezparametrowy
Fibo::Fibo() : digits(1, ZERO){}

//konstruktor ze Stringa
Fibo::Fibo(const std::string& s){
	assert(s[0] == '1');
	for(auto it = s.rbegin(); it != s.rend(); it++){
		assert(*it == '0' || *it == '1');
		digits.push_back(*it == '1');
	}
	normalize();
}

Fibo::Fibo(const char *c){
	assert(c != nullptr);
	digits = move(Fibo(std::string(c)).digits);
}

//copy konstruktor
Fibo::Fibo(const Fibo& other) = default;

//move konstruktor
Fibo::Fibo(Fibo&& other) : digits(move(other.digits)){}

namespace{
	bool iterate_until_repetition(const Digits& d, size_t& current_index){
		Digit current_value = d[current_index];
		while(current_index > 0){
			if(d[current_index - 1] == current_value){
				current_index--;
				return true;
			}
			current_index--;
			current_value = d[current_index];
		}
		return false;
	}

	void
	handle_doubled_ones(Digits& d, size_t& current_index, size_t& free_slot){
		d[free_slot] = ONE;
		for(size_t i = free_slot; i-- > current_index;){
			d[i] = ZERO;
		}
		free_slot = current_index;
	}
}

//zmienia do postaci unormowanej
void Fibo::normalize(){
	digits.push_back(ZERO);
	size_t free_slot = digits.size() - 1;
	size_t current_index = digits.size() - 1;
	while(iterate_until_repetition(digits, current_index)){
		if(digits[current_index] == 0){
			free_slot = current_index;
		}else{
			handle_doubled_ones(digits, current_index, free_slot);
		}
	}

	while(digits.back() == 0 && digits.size() > 1){
		digits.pop_back();
	}
}

namespace{
	size_t greatest_fitting_fib(unsigned long long n){
		size_t i = 0;
		while(fib_n(i + 1) <= n){
			i++;
		}
		return i;
	}
}

//główny konstruktor liczbowy
Fibo::Fibo(unsigned long long n){
	if(n == 0){
		digits.push_back(ZERO);
		return;
	}

	size_t i = greatest_fitting_fib(n);
	digits.resize(i - 1);
	for(; i >= 2; i--){
		if(fib_n(i) <= n){
			set_digit(i, ONE);
			n -= fib_n(i);
		}
	}
}

Fibo::Fibo(int n){
	assert(n >= 0);
	digits = move(Fibo((unsigned long long) n).digits);
}

Fibo::Fibo(unsigned int n) : Fibo((unsigned long long) n){}

Fibo::Fibo(long n){
	assert(n >= 0);
	digits = move(Fibo((unsigned long long) n).digits);
}

Fibo::Fibo(unsigned long n){}

Fibo::Fibo(long long n){
	assert(n >= 0);
	digits = move(Fibo((unsigned long long) n).digits);
}

void Fibo::add_one_at_position(size_t i){
	digits.push_back(ZERO);

	size_t add_at = i;
	while(add_at >= 0){
		if(digits[add_at] == 1){
			digits[add_at + 1] = ONE;
			digits[add_at] = ZERO;
			if(add_at < 2){
				break;
			}else{
				add_at -= 2;
			}
		}else{
			digits[add_at] = ONE;
			break;
		}
	}
	normalize();
}

Fibo& Fibo::operator+=(const Fibo& other){
	if(this == &other){
		return *this;
	}

	if(other.digits.size() > digits.size()){
		digits.resize(other.digits.size());
	}

	for(size_t i = 0; i < other.digits.size(); i++){
		if(other.digits[i] == 1){
			add_one_at_position(i);
		}
	}

	return *this;
}

const Fibo operator+(Fibo a, const Fibo& b){
	return a += b;
}

const Fibo operator+(long long a, const Fibo& b){
	return Fibo(a) += b;
}

Fibo& Fibo::operator=(Fibo&& other){
	digits = move(other.digits);
	return *this;
}

Fibo& Fibo::operator=(const Fibo& other) = default;

Fibo& Fibo::operator<<=(long long n){
	assert(n >= 0);
	Digits zeroes(n);
	zeroes.insert(zeroes.end(), make_move_iterator(digits.begin()),
			make_move_iterator(digits.end()));
	digits = move(zeroes);
	normalize();
	return *this;
}

const Fibo operator<<(Fibo a, long long n){
	return a <<= n;
}

Fibo& Fibo::operator&=(const Fibo& other){
	size_t length = std::min(this->length(), other.length());
	for(size_t i = 0; i < length; i++){
		digits[i] = digits[i] && other.digits[i];
	}
	normalize();
	return *this;
}

const Fibo operator&(Fibo a, const Fibo& b){
	return a &= b;
}

Fibo& Fibo::operator|=(const Fibo& other){
	size_t length = std::min(this->length(), other.length());
	for(size_t i = 0; i < length; i++){
		digits[i] = digits[i] || other.digits[i];
	}
	normalize();
	return *this;
}

const Fibo operator|(Fibo a, const Fibo& b){
	return a |= b;
}

Fibo& Fibo::operator^=(const Fibo& other){
	size_t length = std::min(this->length(), other.length());
	for(size_t i = 0; i < length; i++){
		digits[i] = digits[i] ^ other.digits[i];
	}
	normalize();
	return *this;
}

const Fibo operator^(Fibo a, const Fibo& b){
	return a ^= b;
}

const bool Fibo::operator==(const Fibo& other) const{
	if(length() != other.length()){
		return false;
	}

	for(size_t i = 0; i < length(); i++){
		if(digits[i] != other.digits[i]){
			return false;
		}
	}
	return true;
}

const bool Fibo::operator!=(const Fibo& other) const{
	return !(*this == other);
}

const bool Fibo::operator<(const Fibo& other) const{
	if(length() > other.length()){
		return false;
	}

	if(length() < other.length()){
		return true;
	}

	size_t i = length() - 1;
	for(auto it = digits.rbegin(); it != digits.rend(); it++){
		if(*it && !other.digits[i]){
			return false;
		}
		if(!(*it) && other.digits[i]){
			return true;
		}
		i--;
	}
	return false;
}

const bool Fibo::operator>(const Fibo& other) const{
	return (*this != other) && !(*this < other);
}

const bool Fibo::operator<=(const Fibo& other) const{
	return !(*this > other);
}

const bool Fibo::operator>=(const Fibo& other) const{
	return !(*this < other);
}

const bool operator==(long long a, const Fibo& b){
	return b == Fibo(a);
}

const bool operator!=(long long a, const Fibo& b){
	return b != Fibo(a);
}

const bool operator<(long long a, const Fibo& b){
	return b > Fibo(a);
}

const bool operator>(long long a, const Fibo& b){
	return b < Fibo(a);
}

const bool operator<=(long long a, const Fibo& b){
	return b >= Fibo(a);
}

const bool operator>=(long long a, const Fibo& b){
	return b <= Fibo(a);
}

size_t Fibo::length() const{
	return digits.size();
}

std::ostream& operator<<(std::ostream& os, const Fibo& fibo){
	for(auto it = fibo.digits.rbegin(); it != fibo.digits.rend(); it++){
		if(*it){
			os << "1";
		}else{
			os << "0";
		}
	}
	return os;
}

const Fibo& Zero(){
	static const Fibo zero;
	return zero;
}

const Fibo& One(){
	static const Fibo one("1");
	return one;
}