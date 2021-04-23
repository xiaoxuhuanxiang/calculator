#pragma once
#include "Executor.h"
class Executor_RPN :
	public Executor
{
public:
	Executor_RPN() {};
	~Executor_RPN() {};
	virtual void setInput(const string &input);
	virtual int execute();
	virtual value_v_base* getResult();
private:
	void clean(queue<value_c*> &theParserRes);
};

