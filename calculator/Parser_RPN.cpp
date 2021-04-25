#include "Parser_RPN.h"
#include <iostream>
#include <ctype.h>
#include <algorithm>
Parser_RPN::Parser_RPN()
{

}

Parser_RPN::~Parser_RPN()
{

}

void Parser_RPN::setInput(const string &input)
{
	m_parser_data = input;
}

int Parser_RPN::pushValue(string::iterator &it, string::iterator &itStart, string::iterator &itEnd, queue<value_c*> &theRes)
{
	if (itEnd > itStart)
	{
		string val(itStart, itEnd);
		value_c *vc = new value_c();
		if (vc->Init(val, it - m_parser_data.begin(), false))
		{
			cout << "the value input is not valid, pos = " << it - m_parser_data.begin() << endl;
			return -1;
		}
		theRes.push(vc);
		return 0;
	}
	else
	{
		return -1;
	}
}
int Parser_RPN::dealWithOper(string::iterator &it, string::iterator &itStart, string::iterator &itEnd,
	stack<value_c*> &theStack, queue<value_c*> &theRes)
{
	string crtOper(it, it + Global::getMaxOperByte());
	int len;
	operType theType = Global::getOperType(crtOper, len);
	if (theType != OPER_NUM)
	{
		itStart = it + len;
		itEnd = itStart;
		
		string theOper(it, it + len);
		value_c *oc = new value_c();
		if (oc->Init(theOper, it - m_parser_data.begin(), true))
		{
			delete oc;
			cout << "the oper input is not valid, pos = " << it - m_parser_data.begin() << endl;
			return -1;
		}
		if (theType == OPER_LPTH)  //左括号无条件入栈
		{
			theStack.push(oc);
		}
		else if (theType == OPER_RPTH)  //右括号出栈入列,直到匹配到第一个左括号
		{
			delete oc;
			while (1)
			{
				value_c *p = theStack.top();
				if (p->isOper() && p->getOperType() == OPER_LPTH)
				{
					theStack.pop();
					delete p;
					break;
				}
				else
				{
					theRes.push(p);
					theStack.pop();
					if (theStack.empty())
					{
						cout << "the right parentheses oper input is not valid, pos = " << it - m_parser_data.begin() << endl;
						return -1;
					}
				}
			}
		}
		else if (theStack.empty())
		{
			if (oc->getOperType() == OPER_RPTH)
			{
				delete oc;
				cout << "the right parentheses oper input is not valid, pos = " << it - m_parser_data.begin() << endl;
				return -1;
			}
			if (theRes.empty())
			{
				delete oc;
				cout << "the oper input is not valid, pos = " << it - m_parser_data.begin() << endl;
				return -1;
			}
			theStack.push(oc);
		}
		else
		{
			int crtPrior = Global::getOperPrior_type(oc->getOperType());
			while (!theStack.empty())
			{
				value_c *p = theStack.top();
				int stackTopPrior = Global::getOperPrior_type(p->getOperType());
				if (crtPrior > stackTopPrior)
				{
					theStack.push(oc);
					break;
				}
				else
				{
					theRes.push(p);
					theStack.pop();
					if (theStack.empty())
					{
						theStack.push(oc);
						break;
					}
				}
			}
		}
		it += (len - 1);
	}
	else
	{
		std::cout << "come across some character that cannot be identified, pos =" << it - m_parser_data.begin() << endl;
		return -1;
	}
	return 0;
}

int Parser_RPN::getRes(queue<value_c*> &theRes)  
{
	if (m_parser_data.empty()) return -1;
	stack<value_c*> theStack;
	int res;
	m_parser_data.erase(remove_if(m_parser_data.begin(), m_parser_data.end(), ::isspace), m_parser_data.end());
	string::iterator itStart = m_parser_data.begin();
	string::iterator itEnd = itStart;
	char *lc;
	for (string::iterator it = m_parser_data.begin(); it != m_parser_data.end(); ++it)
	{
		if (itStart == m_parser_data.begin()) lc = NULL;
		else lc = &(*(it - 1));
		if (Global::isPartOfNumber(*it,lc))  //数字的一部分
		{
			++itEnd;
			if (it == m_parser_data.end() - 1)
			{
				res = pushValue(it, itStart, itEnd, theRes);
				if (res < 0) return res;
			}
			else if (!Global::isPartOfNumber(*(it + 1), &(*it)))
			{
				res = pushValue(it, itStart, itEnd, theRes);
				if (res < 0) return res;
			}
		}
		else 
		{
			res = dealWithOper(it, itStart, itEnd, theStack, theRes);
			if (res < 0) return res;
		}
	}

	while (!theStack.empty())
	{
		value_c *p = theStack.top();
		theRes.push(p);
		theStack.pop();
	}
	return 0;
}
