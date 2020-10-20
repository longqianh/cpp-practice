#include "cal.h"
#include <iostream>
using namespace std;

int main()
{
	Calculator cal;
	// test
	// 1. 2.34+cos(-3.15*2) 负数测试
	// 2. sqrt(((200+2*3)^2+(200.8-2)^2)/20) 括号测试
	// 3. (4!*2)^2/209 阶乘测试
	// 4. exp(cos(tan(arcsin(0.58)))) 函数测试
	// 5. ln(1+sin(1+(2*3!)^2)) 复杂功能测试

	// string test="sqrt(((200+2*3)^2+(200.8-2)^2)/20)";//"sin(1+exp(cos(tan(arcsin(0.58)))))";
	string test="ln(1+sin(1+(2*3!)^2))";//"2.34+cos(-3.15*2)";
	cal.set_input(test);
	cal.calculate();
	cout<<cal.get_output()<<endl;
	return 0;
}
