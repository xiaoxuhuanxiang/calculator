#pragma once
#include "value_c.h"
#include <queue>
#include <string>
class Parser
{
public:
	Parser() {};
	~Parser() {};

	virtual void setInput(const std::string &input) = 0;
	virtual int getRes(std::queue<value_c*> &theRes) = 0;
};

