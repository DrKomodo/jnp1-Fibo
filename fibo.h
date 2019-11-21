#ifndef JNP1_FIBO_FIBO_H
#define JNP1_FIBO_FIBO_H

#include <vector>
#include <iostream>
#include <cstring>

using Digit = bool;
using Digits = std::vector<Digit>;

class Fibo{

public:
	//konstruktory podstawowe
	Fibo();
	Fibo(const Fibo& other);
	Fibo(Fibo&& other);

	//konstruktory znakowe
	explicit Fibo(const std::string& s);
	explicit Fibo(const char *);

	//konstruktory liczbowe
	Fibo(int n);
	Fibo(unsigned int n);
	Fibo(long n);
	Fibo(unsigned long n);
	Fibo(long long n);
	Fibo(unsigned long long n);

	//konstruktory niedozwolone
	explicit Fibo(char a) = delete;
	explicit Fibo(bool a) = delete;

	//operatory przypisujące
	Fibo& operator+=(const Fibo& other);
	Fibo& operator=(Fibo&& that) noexcept;
	Fibo& operator=(const Fibo& other);
	Fibo& operator<<=(long long n);
	Fibo& operator&=(const Fibo& other);
	Fibo& operator|=(const Fibo& other);
	Fibo& operator^=(const Fibo& other);

	//operatory porównujące fibo z fibo
	bool operator==(const Fibo& other) const;
	bool operator!=(const Fibo& other) const;
	bool operator<(const Fibo& other) const;
	bool operator>(const Fibo& other) const;
	bool operator<=(const Fibo& other) const;
	bool operator>=(const Fibo& other) const;

	friend std::ostream& operator<<(std::ostream& os, const Fibo& fibo);
	size_t length() const;

private:
	Digits digits;
	bool iterate_until_repetition(size_t& current_index) const;
	void handle_pair_of_one(size_t& current_index, size_t& free_slot);
	void remove_double_ones();
	void pop_zeros();
	void normalize();
	void set_digit(size_t fib_index, bool value);
	void handle_last_operation_in_adding(size_t add_at);
	void add_one_at_position(size_t i);
};

//operatory nieprzypisujące
const Fibo operator+(Fibo a, const Fibo& b);
const Fibo operator+(long long a, const Fibo& b);
const Fibo operator<<(Fibo a, long long n);
const Fibo operator&(Fibo a, const Fibo& b);
const Fibo operator|(Fibo a, const Fibo& b);
const Fibo operator^(Fibo a, const Fibo& b);

//operatory porównujące liczby z fibo
bool operator==(long long a, const Fibo& other);
bool operator!=(long long a, const Fibo& b);
bool operator<(long long a, const Fibo& b);
bool operator>(long long a, const Fibo& b);
bool operator<=(long long a, const Fibo& b);
bool operator>=(long long a, const Fibo& b);

const Fibo& Zero();
const Fibo& One();

#endif
