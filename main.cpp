#include "fibo.h"
#include <cassert>
#include <iostream>

using namespace std;
int main() {

	//EXAMPLE
	Fibo f;

	assert(f == Zero());
	assert(Fibo(f) == Zero());
	assert(Zero() < One());
	assert(Fibo("11") == Fibo("100"));
	assert((Fibo("1001") + Fibo("10")) == Fibo("1011"));
	assert((Fibo("1001") & Fibo("1100")) == Zero()); // 1100 == 10000
	assert((Fibo("1100") | Fibo("11")) == Fibo("10100")); // 1100 == 10000, 11 == 100
	assert((Fibo("1001") ^ Fibo("1010")) == Fibo("11"));
	assert((Fibo("101") << 3) == Fibo("101000"));

	f = One();
	f <<= 3;
	assert(f == Fibo("1000"));

	f = One();
	assert(f + Fibo("1") == Fibo("10"));
	assert(f == One());

	Fibo f1("101");
	Fibo f2 = Fibo("101");
	assert(f1 == f2);

	assert(Fibo("11").length() == 3); // 11 == 100

	std::cout << Fibo("11") << std::endl; // prints 100

	bool b;

	f1 += 2;
	f1 = f2 + 2;
	b = 2 < f2;


	//PO ZDJĘCIU TEGO MA SIE NIE KOMPILOWAC
	/* Fibo f3(true);
    Fibo f4('a');
    f1 += "10";
    f1 = f2 + "10";
    b = "10" < f2;
    Zero() += Fibo("10");
	One() += Fibo("10");
	Fibo(2.09);
	 f4+="101";
	"101"+=f4;*/



	//moje pomysły
	f1+=f1;
	b = f1 < f1;

	size_t a = 5;
	int c = 100000;
	unsigned int d;



	Fibo f3(a);
	Fibo f4(c);

	'a' + f4;
	f4 + 'a';



	cout << "\n" << Fibo("10101010") << " "<<Fibo("10101010").length();
	assert(Fibo("10101010").length() == 8);

	assert(110 == Fibo("110101011"));
	assert(Fibo("110101011") == 110);


	const char* chary = "101011";
	Fibo f5(chary);

	string str = "101011";
	Fibo f6(str);

	assert(Fibo(110) == Fibo("110101011"));
	assert((Fibo("1") + Fibo("10110110")) == Fibo("10110111"));
	assert((Fibo("1001") & Fibo("11000000000000")) == Zero());
	assert((Fibo("1010") | Fibo("101")) == Fibo("1111"));

	//ASERCJE po odpaleniu
	//Fibo(-2);
	//Fibo("1adfsdfs");
	//Fibo("001");
	//b = -2 < f1;
	//b = f1 > -2;
	//const char* null = nullptr;
	//Fibo f5(null);
	//Fibo("101") << -3;








}