#pragma once
#include "Parser.h"
#include <queue>
#include <stack>

using namespace std;
//逆波兰表达式解析器
class Parser_RPN :
	public Parser
{
public:
	Parser_RPN();
	~Parser_RPN();
	
	virtual void setInput(const std::string &input);
	virtual int getRes(queue<value_c*> &theRes);  //获取逆波兰表达式的结果队列
private:
	string m_parser_data;
	int dealWithOper(string::iterator &it, string::iterator &itStart, string::iterator &itEnd,
		stack<value_c*> &theStack, queue<value_c*> &theRes);
	int pushValue(string::iterator &it, string::iterator &itStart, string::iterator &itEnd, queue<value_c*> &theRes);
	
};

