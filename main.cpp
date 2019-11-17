#include <iostream>
#include <vector>

using Digit = bool;
using Digits = std::vector<Digit>;



// Pytania:
//czy argument do konstruktora ma byc przez referencje?
//co ma byc w .cpp a co w .h?
//jak inicjowac member objects kiedy argumenty ich oknstruktorow trzeba najpierw obliczyć?

//zmienic na naturalne indeksowanie cyfr od najmniej znaczacych

unsigned long fib(unsigned const int n) {
    static std::vector<unsigned long> fib_numbers(2);
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

class Fibo {
    Digits digits;

    void normalize();

    void set_digit(const unsigned fib_index, int value) {
        digits[fib_index - 2] = value == 1;
    }

    void add_one_at_position(unsigned i);

public:
    void print() { //funkcja robocza
        for (auto it = digits.rbegin(); it != digits.rend(); it++) {
            if (*it) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }

    explicit Fibo(const std::string &s) { //co zrobic gdy s nie jest ciagiem zer i jedynek? (na razie zakladam ze jest)
        for (auto it = s.rbegin(); it != s.rend(); it++) {
            digits.push_back(*it == '1');
        }
        normalize();
    }

    explicit Fibo(unsigned int n);

    Fibo &operator+=(const Fibo &other);
};

namespace {
    bool iterate_until_repetition(Digits &d, unsigned long &current_index) {
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

    void handle_doubled_ones(Digits &d, unsigned long &current_index, unsigned long &free_slot) {
        d[free_slot] = 1;
        for (unsigned long i = free_slot - 1; i >= current_index; i--) {
            d[i] = 0;
        }
        free_slot = current_index;
    }
}

void Fibo::normalize() {
    digits.push_back(0);
    unsigned long free_slot = digits.size() - 1;
    unsigned long current_index = digits.size() - 1;
    while (iterate_until_repetition(digits, current_index)) {
        if (digits[current_index] == 0) {
            free_slot = current_index;
        } else {
            handle_doubled_ones(digits, current_index, free_slot);
        }
    }

    while (digits.back() == 0) {
        digits.pop_back();
    }
}

Fibo::Fibo(unsigned int n) {
    unsigned int i = 0;
    while (fib(i + 1) <= n) {
        i++;
    }

    digits.resize(i - 1);
    for (; i >= 2; i--) {
        if (fib(i) <= n) {
            set_digit(i, 1);
            n -= fib(i);
        }
    }
}




void Fibo::add_one_at_position(const unsigned i) {
    if (digits[i] == 0) {
        digits[i] = 1;
        normalize();
        return;
    }

    digits.push_back(0);
    unsigned add_at = i;
    while (add_at >= 0) {
        if (digits[add_at] == 1) {
            digits[add_at + 1] = 1;
            digits[add_at] = 0;
            add_at -= 2;
        } else {
            digits[add_at] = 1;
            break;
        }
    }
    normalize();
}

Fibo &Fibo::operator+=(const Fibo &other) {
    if (this == &other) {
        return *this;
    }

    if (other.digits.size() > digits.size()) {
        digits.resize(other.digits.size());
    }

    for (unsigned i = 0; i < other.digits.size(); i++) {
        if (other.digits[i] == 1) {
            add_one_at_position(i);
        }
    }

    return *this;
}

int main() {
    Fibo f2(50);
    Fibo f3(20);

    f2.print();
    f3.print();

    f2 += f3;

    f2.print();


    return 0;
}