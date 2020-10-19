#include "cal.h"
#include <iostream>
using namespace std;

int main()
{
	Calculator cal;
	string test="(3/sin(-3.1+2))*3";
	cal.set_input(test);
	cal.calculate();
	cout<<cal.get_output()<<endl;
	return 0;
}
