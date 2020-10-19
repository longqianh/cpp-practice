#include "cal.h"
using namespace std;

Calculator::Calculator():_output(0){}
Calculator::~Calculator(){}

void Calculator::set_input(string expr)
{
	_input=expr;
}


bool Calculator::isop(char op)
{
	return op=='+'||op=='-'||op=='*'||op=='/'||op=='^';
}

int Calculator::opclass(char op)
{

	switch(op)
	{
		case '+': case '-' : return 1;
		case '*': case '/' : return 2;
		case '^': case '!': return 3;
		default : return 0;
	}
}

string Calculator::char2string(char op)
{
	switch(op)
	{
		case '+': return "+";
		case '-': return "-"; 
		case '*': return "*"; 
		case '/': return "/";
		case '^': return "^";
		case '!': return "!";
		default : return "";
	}
}

bool Calculator::compare_op(char op1,char op2)
{
	return(opclass(op1)>opclass(op2));
}

bool Calculator::verify(string expr)
{
	int tmpl,tmpr=0;
	for(int i=0;i<expr.length();i++)
	{
		if(expr[i]=='(')
		{	
			tmpl++;
			if(i>0&&isdigit(expr[i-1]))
				return false;

		}
		if(expr[i]==')')
		{
			if(tmpl==0)return false;
			tmpr++;
		}	
		if(i<expr.length()-1)
		{
			if(expr[i]=='!'&&isdigit(expr[i+1]))return false;
			if(isop(expr[i])&&isop(expr[i+1]))return false;
		}
	}
	if(tmpl!=tmpr)return false;
	if(isalpha(expr[expr.length()-1]))return false;
	return true;
}




double Calculator::Gamma(double xx) // 浮点数阶乘
{
	double x, y, tmp, ser;
    double cof[] = {76.18009172947146,-86.50532032941677,24.01409824083091,-1.231739572450155,0.1208650973866179e-2,-0.5395239384953e-5};
    int j;
    x = xx;
    y = x;
    tmp = x + 5.5;
    tmp -= (x + 0.5) * log(tmp);
    ser = 1.000000000190015;
    for (j = 0; j <= 5; j++)
    {
        ser += cof[j] / (++y);
    }
    
    return xx*exp((-tmp + log(2.5066282746310005 * ser / x)));

}

double Calculator::simple_cal(double x, double y, char op) // type of string[k]: char
{
    if (op == '+')
        return x + y;
    if (op == '-')
        return x - y;
    if (op == '*')
        return x * y;
    if (op == '/')
        return x / y;
    if (op == '^')
        return pow(x, y);

    return 0;
}

double Calculator::func_cal(double x,string func)
{
    if(func=="sin") return sin(x);
    if(func=="cos") return cos(x);
    if(func=="tan") return sin(x);
    if(func=="arcsin") return asin(x);
    if(func=="arccos") return acos(x);
    if(func=="arccos") return atan(x);
    if(func=="sqrt") return sqrt(x);
    if(func=="exp") return exp(x);
    if(func=="ln") return log(x);
    if(func=="lg") return log10(x);
    if(func=="ceil") return ceil(x);
    if(func=="floor") return floor(x);
    if(func=="abs") return fabs(x);
    return ERROR;
}


	
void Calculator::parse_expr(string expr)
{
	bool func_flag=false;
	int n=expr.length();
	int i=0;

	while(i<n)
	{
		// debug
		// cout<<"expr: "<<expr[i]<<endl;
		// if(!S1.empty())cout<<"S1: "<<S1.top()<<endl;
		// if(!S2.empty())cout<<"S2: "<<S2.back()<<endl;
		// if(!S3.empty())cout<<"S3: "<<S3.back()<<endl;
		
		// 处理数字
		if( (i==0&&expr[i]=='-')
			|| (i>0&&expr[i-1]=='('&&expr[i]=='-')
			|| isdigit(expr[i]) ) 
		{

			string tmp_num;

			if(i==0&&expr[i]=='-')
			{
				tmp_num+='-';
				i++;
			}
			else if (i>0&&expr[i-1]=='('&&expr[i]=='-') // minus number
			{
				S1.push('(');
				tmp_num+='-';
				i++;
			}

			while(i<n&&(isdigit(expr[i])||expr[i]=='.'||expr[i]=='!'))
			{
				tmp_num+=expr[i++];
			}
			i--;
			

			if(func_flag){ S3.push(tmp_num); }
			else S2.push(tmp_num);
			cout<<"digit process success"<<endl;
	
		}
		
		//处理左括号
		else if(expr[i]=='('||isalpha(expr[i])) 
		{
			if(expr[i]=='(') S1.push('(');
			else{
				string tmp_func;
				while(expr[i]!='(')
				{
					tmp_func+=expr[i++];
				}
				S3.push(tmp_func);
				func_flag=true;
				S1.push('(');
			}
		
		}
		
		else if(isop(expr[i]))
		{
			if(S1.empty())	S1.push(expr[i]);
			else if(compare_op(expr[i],S1.top())) S1.push(expr[i]);
			else {
					if(func_flag){
						S3.push(char2string(S1.top()));
						S1.pop();
						S1.push(expr[i]);
					}
					else{
						S2.push(char2string(S1.top()));
						S1.pop();
						S1.push(expr[i]);
				} 
			}
		}
		
		else if(expr[i]==')')
		{
			if(!S1.empty())
			{
				char tmp=S1.top();
				S1.pop();

				while(tmp!='(')
				{
						
					if(func_flag) S3.push(char2string(tmp));
					else S2.push(char2string(tmp));					
					tmp=S1.top();
					S1.pop();
					cout<<"S1 pop success"<<endl;

				}

				
			}
			if(func_flag)
			{
				S2.push(to_string(cal_repolish(S3))); //double2string
				func_flag=false;	
			}
			
		}
		i++;

	}

	cout<<"last things"<<endl;

	while(!S1.empty())
	{
		if(func_flag) S3.push(char2string(S1.top()));
		else S2.push(char2string(S1.top()));
		S1.pop();
		cout<<"S1 pop success"<<endl;

	}

	if(func_flag)
	{
		S2.push(to_string(cal_repolish(S3))); //double2string
		func_flag=false;	
	}

	cout<<"Parse expr success"<<endl;


}


double Calculator::cal_repolish(queue<string> q)
{
	string func;
    bool flag = false;
    stack<double> S;
    while (!q.empty())
    {
        string tmp = q.front();

        cout << tmp << endl;
        q.pop();
        if (isdigit(tmp[0])||(tmp[0]=='-'&&isdigit(tmp[1])))
        {
            if (tmp[tmp.length() - 1] == '!')
            {
                S.push(Gamma(stod(tmp)));
            }
            else
                S.push(stod(tmp));
        }
        else if (isalpha(tmp[0]))
        {
            func=tmp;
            flag=true;
            continue;   
        }
        else if(isop(tmp[0]))
        {
            double tmpr = S.top();
            S.pop();
            double tmpl = S.top();
            S.pop();
            S.push(simple_cal(tmpl,tmpr, tmp[0]));
        }

    }
    if(flag) return func_cal(S.top(),func);
    return S.top();
}


void Calculator::calculate()
{
	if(!verify(_input)) {
		cout<<"ERROR input!"<<endl;
		_output=ERROR;
	}
	parse_expr(_input);

	_output = cal_repolish(S2);
}