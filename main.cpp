#include <iostream>
#include "fibo.h"

using namespace std;

int main() {

   Fibo a("10101");
   Fibo b(15);
   Fibo f('a');

   Fibo c;
   a = c;

   a.print();



    return 0;
}
