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


bool Fibo::iterate_until_repetition(size_t& current_index) const {
	Digit current_value = digits[current_index];
	while(current_index > 0){
		if(digits[current_index - 1] == current_value){
			current_index--;
			return true;
		}
		current_index--;
		current_value = digits[current_index];
	}
	return false;
}

//usuwa jedno powtórzenie jedynek
void Fibo::handle_pair_of_one(size_t& current_index, size_t& free_slot){
	digits[free_slot] = ONE;
	for(size_t i = free_slot; i-- > current_index;){
		digits[i] = ZERO;
	}
	free_slot = current_index;
}

//usuwa wiodące zera
void Fibo::pop_zeros(){
	while(digits.back() == 0 && digits.size() > 1){
		digits.pop_back();
	}
}

//zamienia powtórzenia jedynki
void Fibo::remove_double_ones(){
	digits.push_back(ZERO);
	size_t free_slot = digits.size() - 1;
	size_t current_index = digits.size() - 1;
	while(iterate_until_repetition(current_index)){
		if(digits[current_index] == 0){
			free_slot = current_index;
		}else{
			handle_pair_of_one(current_index, free_slot);
		}
	}
}

//zmienia do postaci unormowanej
void Fibo::normalize(){
	remove_double_ones();
	pop_zeros();
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

Fibo::Fibo(unsigned long n) : Fibo((unsigned long long) n){}

Fibo::Fibo(long long n){
	assert(n >= 0);
	digits = move(Fibo((unsigned long long) n).digits);
}

//jeśli pętla doszła do końca ustawia ostatnie 2 cyfry
void Fibo::handle_last_operation_in_adding(size_t add_at){
	if(add_at == 1){
		if(digits[add_at] == ONE){
			digits[2] = ONE;
			digits[1] = ZERO;
			digits[0] = ONE;
		}else{
			digits[1] = ONE;
		}
	}

	if(add_at == 0){
		if(digits[0] == ONE){
			digits[1] = ONE;
			digits[0] = ZERO;
		}else{
			digits[0] = ONE;
		}
	}
}

void Fibo::add_one_at_position(size_t add_at){
	digits.push_back(ZERO);

	while(add_at >= 2){
		if(digits[add_at] == ONE){
			digits[add_at + 1] = ONE;
			digits[add_at] = ZERO;
			add_at -= 2;
		}else{
			digits[add_at] = ONE;
			break;
		}
	}
	if(add_at < 2){
		handle_last_operation_in_adding(add_at);
	}
	remove_double_ones();
}

Fibo& Fibo::operator+=(const Fibo& other){
	if(this == &other){
		return *this += Fibo(other);
	}

	size_t length = other.length();
	if(length > this->length()){
		digits.resize(length, ZERO);
	}

	for(size_t i = 0; i < length; i++){
		if(other.digits[i] == ONE){
			add_one_at_position(i);
		}
	}

	pop_zeros();
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

	size_t length = other.length();
	if(length > this->length()){
		digits.resize(length, ZERO);
	}

	size_t i = 0;
	for(; i < length; i++){
		digits[i] = digits[i] && other.digits[i];
	}

	while(i < this->length()){
		digits[i] = ZERO;
		i++;
	}

	normalize();
	return *this;
}

const Fibo operator&(Fibo a, const Fibo& b){
	return a &= b;
}

Fibo& Fibo::operator|=(const Fibo& other){
	size_t length = other.length();
	if(length > this->length()){
		digits.resize(length, ZERO);
	}

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
	size_t length = other.length();
	if(length > this->length()){
		digits.resize(length, ZERO);
	}

	for(size_t i = 0; i < length; i++){
		digits[i] = digits[i] ^ other.digits[i];
	}
	normalize();
	return *this;
}

const Fibo operator^(Fibo a, const Fibo& b){
	return a ^= b;
}

bool Fibo::operator==(const Fibo& other) const{
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

bool Fibo::operator!=(const Fibo& other) const{
	return !(*this == other);
}

bool Fibo::operator<(const Fibo& other) const{
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

bool Fibo::operator>(const Fibo& other) const{
	return (*this != other) && !(*this < other);
}

bool Fibo::operator<=(const Fibo& other) const{
	return !(*this > other);
}

bool Fibo::operator>=(const Fibo& other) const{
	return !(*this < other);
}

bool operator==(long long a, const Fibo& b){
	return b == Fibo(a);
}

bool operator!=(long long a, const Fibo& b){
	return b != Fibo(a);
}

bool operator<(long long a, const Fibo& b){
	return b > Fibo(a);
}

bool operator>(long long a, const Fibo& b){
	return b < Fibo(a);
}

bool operator<=(long long a, const Fibo& b){
	return b >= Fibo(a);
}

bool operator>=(long long a, const Fibo& b){
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