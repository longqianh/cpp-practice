#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <ctype.h>
#include <math.h>
#define ERROR -1000001
using namespace std;

class Calculator
{
public:
    Calculator();
    ~Calculator();
    void set_input(string expr);
    void calculate(); // calculate reverse polish expression
    
    double get_output(){ return _output; }

private:
    void parse_expr(string expr);
    bool isop(char op);
    bool compare_op(char op1, char op2);
    int opclass(char op);
    bool verify(const string expr);
    double Gamma(double xx);
    double simple_cal(double x, double y, char op);
    double func_cal(double x,string func);
    double cal_repolish(queue<string>& q);
    string char2string(char op);
    string _input;
    double _output;
    stack<char> S1;
    queue<string> S2;
    queue<string> S3;
};