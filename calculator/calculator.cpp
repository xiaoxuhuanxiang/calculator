// calculator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Executor.h"
#include "Executor_RPN.h"
#include "value_v_base.h"
#include "value_v.h"
using namespace std;
int main(int argc, char *argv[])
{
	vector<string> testExample;
	testExample.push_back("1+2+3+4");     //正常加法
	testExample.push_back("1+2*3+4");     //有乘法存在，考虑优先级
	testExample.push_back("(1+2)*3+4");   //有乘法有括号
	testExample.push_back("(01+2)*03+4"); //有0开头的数字
	testExample.push_back("1/2+3*5+(012.53+09.8/02)*6"); //有0开头数字，有小数，有括号和高优先级运算符
	testExample.push_back("1/2+3*5-(012.53+09.8/02)*6"); //加减乘除，括号，小数
	for (size_t ix = 0; ix < testExample.size(); ++ix)
	{
		Executor *p = new Executor_RPN();
		p->setInput(testExample[ix]);
		if (p->execute())
		{
			delete p;
			continue;
		}
		value_v_base *res = p->getResult();
		cout << testExample[ix] << "=";
		res->print();
		delete p;
	}
	
	system("pause");
}
