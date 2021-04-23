#pragma once
#include "global.h"
#include "value_c.h"
class value_v_base
{
public:
	value_v_base() {};
	~value_v_base() {};
	virtual void reset() = 0;
	virtual void print() = 0;
	virtual int Init(value_c *vc) = 0;
	virtual int executeFunction(value_v_base *v1, value_v_base *v2, operType ot) = 0;
};


