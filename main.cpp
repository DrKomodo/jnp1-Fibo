#include "fibo.h"

#include <cassert>
#include <iostream>

using namespace std;
int main() {

	Fibo f1;

	Fibo f2("10011");
	unsigned int kkk = 5;
	f2 = Fibo(kkk);
	bool b;
	f1 += 2;
	cout << (f1 = f2 + 2);
	cout << (f1 = 2 + f2);


}