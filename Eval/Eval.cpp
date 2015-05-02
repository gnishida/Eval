#include "Eval.h"
#include <stack>
#include <boost/spirit.hpp>

using namespace boost::spirit;

namespace eval {

stack<double> stk; //stack<int> stk;

void push(double n) //push(int n)
{
	stk.push(n);
}

double pop()  //int pop()
{
	double t = stk.top(); //int t = stk.top();
	stk.pop();
	return t;
}

void clear()
{
	stk = stack<double>();  //stk = stack<int>();
}

//-----------------------------------------------------------------------------
//	セマンティックアクション
//-----------------------------------------------------------------------------

void PUSH(double n) //PUSH(int n)
{
	stk.push( n );
}

void ADD(const char* const, const char* const)
{
	double a = pop();//int a = pop();
	double b = pop();//int b = pop();
	push(a + b);
}

void SUB(const char* const, const char* const)
{
	double a = pop();//int a = pop();
	double b = pop();//int b = pop();
	push(b - a);
}

void MUL(const char* const, const char* const)
{
	double a = pop();//int a = pop();
	double b = pop();//int b = pop();  
	push(a * b);
}

void DIV(const char* const, const char* const)
{
	double a = pop();//int a = pop();
	double b = pop();//int b = pop();
	push(b / a);
}

void POW(const char* const, const char* const)
{
	double a = pop();//int a = pop();
	double b = pop();//int b = pop();
	push(pow(b,a));
}

//-----------------------------------------------------------------------------
//	文法
//-----------------------------------------------------------------------------
struct calculator : public grammar<calculator> {
	template<typename S> struct definition {
		rule<S> expression, term, factor, group;

		definition(const calculator& self) {
			group		= '(' >> expression >> ')';
			factor		= real_p[&PUSH] | group;
			term		= factor >> *( ('*' >> factor)[&MUL] |
				                       ('/' >> factor)[&DIV] |
									   ('^' >> factor)[&POW]   );
			expression	= term >> *( ('+' >> term)[&ADD] | ('-' >> term)[&SUB] );
		}

		// 開始記号を定義
		const rule<S>& start() const { return expression; }	
	};
};

double eval(string str) {
	calculator calc;

	// 入力された文字列をcalcに入力し、space_p(空白、タブ、改行)を抜いて解析
	parse_info<> r = parse(str.c_str(), calc, space_p);

	if (r.full) {
		return pop();
	} else {
		return 999999;
	}
}

}
