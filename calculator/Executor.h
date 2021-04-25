#pragma once
#include "Parser.h"
#include "value_v_base.h"
#include "value_c.h"
class Executor
{
public:
	Executor();
	virtual	~Executor();
	virtual void setInput(const string &input) = 0;
	virtual int execute() = 0;
	virtual value_v_base* getResult() = 0;
protected:
	Parser *m_theParser;
	queue<value_c *> m_theQueue;
	value_v_base* m_res;
};

