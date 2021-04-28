#include "Executor_RPN.h"
#include "Parser_RPN.h"
#include "value_v.h"
#include <iostream>
using namespace std;
void Executor_RPN::setInput(const string &input)
{
	if (m_theParser != 0) delete m_theParser;
	m_theParser = new Parser_RPN();
	m_theParser->setInput(input);
}

void Executor_RPN::clean(queue<value_c*> &theParserRes)
{
	while (!theParserRes.empty())
	{
		value_c *p = theParserRes.front();
		theParserRes.pop();
		delete p;
	}
}

int Executor_RPN::execute()
{
	queue<value_c*> theParserRes;
	m_theParser->getRes(theParserRes);
	if (theParserRes.size() == 1)
	{
		value_c *vc = theParserRes.front();
		m_res = new value_v();
		if (vc->isOper())
		{
			cout << "cannot calculate since there is only a operator" << endl;
			return -1;
		}
		if (m_res->Init(vc)) return -1;
		else return 0;
	}
	if (theParserRes.size() < 3)
	{
		cout << "the expression is not complete" << endl;
		return -1;
	}
	m_res = new value_v();
	stack<value_v*> theStack;
	while (!theParserRes.empty())
	{
		value_c *vc = theParserRes.front();
		if (!vc->isOper())
		{
			value_v *v = new value_v();
			v->Init(vc);
			theStack.push(v);	
		}
		else
		{
			value_v *v1 = theStack.top();
			theStack.pop();
			value_v *v2 = theStack.top();
			theStack.pop();
			value_v *v = new value_v();
			v->executeFunction(v1, v2, vc->getOperType());
			theStack.push(dynamic_cast<value_v *>(v));
			delete v1;
			delete v2;
		}
		theParserRes.pop();
		delete vc;
	}
	
	if (theStack.size() != 1)
	{
		cout << "unknown error" << endl;
		while (!theStack.empty())
		{
			value_v *p = theStack.top();
			if (p != m_res)
			{
				delete p;
			}
			theStack.pop();
		}
		return -1;
	}

	m_res = theStack.top();
	return 0;
}
value_v_base* Executor_RPN::getResult()
{
	return m_res;
}