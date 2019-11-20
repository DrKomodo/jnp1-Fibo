#ifndef JNP1_FIBO_FIBO_H
#define JNP1_FIBO_FIBO_H

#include <vector>
#include <iostream>

using Digit = bool;
using Digits = std::vector<Digit>;


class Fibo {

public:
	Fibo();
    Fibo(const Fibo& other);
    Fibo(Fibo&& other); //tak podpowiada z tym no except
    explicit Fibo(const std::string &s);
    explicit Fibo(const char*);


	Fibo(int n);
	Fibo(unsigned int n);
	Fibo(long n);
	Fibo(unsigned long n);
	Fibo(long long n);
    Fibo(unsigned long long n);


    explicit Fibo(char a) = delete;
    explicit Fibo(bool a) = delete;

    //TODO czy to nie powinno byc const oraz & wszedzie z przodu, co daje const z tyłu?
    Fibo& operator+=(const Fibo &other);
    Fibo& operator=(Fibo&& that); //move
    Fibo& operator=(const Fibo& other);
	Fibo& operator<<=(long long n);
	Fibo& operator&=(const Fibo &other);
	Fibo& operator|=(const Fibo &other);
	Fibo& operator^=(const Fibo &other);

	const bool operator==(const Fibo &other) const;
	const bool operator!=(const Fibo &other) const;
	const bool operator<(const Fibo &other) const;
	const bool operator>(const Fibo &other) const;
	const bool operator<=(const Fibo &other) const;
	const bool operator>=(const Fibo &other) const;

	friend std::ostream& operator<<(std::ostream& os, const Fibo& fibo);
    size_t length() const;

private:
    Digits digits;
    void normalize();
    void set_digit(size_t fib_index, bool value);
    void add_one_at_position(size_t i);
};

//TODO??lepiej chyba move
const Fibo operator+(Fibo a, const Fibo &b);
const Fibo operator+(long long a , const Fibo &b);
const Fibo operator<<(Fibo a, long long n);
const Fibo operator&(Fibo a, const Fibo &b);
const Fibo operator|(Fibo a, const Fibo &b);
const Fibo operator^(Fibo a, const Fibo &b);


const bool operator==(long long a, const Fibo &other);
const bool operator!=(long long a, const Fibo &b);
const bool operator<(long long a, const Fibo &b);
const bool operator<=(long long a, const Fibo &b);
const bool operator>=(long long a, const Fibo &b);

const Fibo& Zero();
const Fibo& One();

#endif
