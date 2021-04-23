#pragma once
#include "Parser.h"
#include <queue>
#include <stack>

using namespace std;
//�沨�����ʽ������
class Parser_RPN :
	public Parser
{
public:
	Parser_RPN();
	~Parser_RPN();
	
	virtual void setInput(const std::string &input);
	virtual int getRes(queue<value_c*> &theRes);  //��ȡ�沨�����ʽ�Ľ������
private:
	string m_parser_data;
	int dealWithOper(string::iterator &it, string::iterator &itStart, string::iterator &itEnd,
		stack<value_c*> &theStack, queue<value_c*> &theRes);
	int pushValue(string::iterator &it, string::iterator &itStart, string::iterator &itEnd, queue<value_c*> &theRes);
	
};

