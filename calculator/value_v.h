#pragma once
#include <string>
#include "value_v_base.h"
#include "value_c.h"
using namespace std;

class value_v: public value_v_base
{
public:
	value_v();
	~value_v();
	virtual void reset();
	virtual int Init(value_c *vc);
	virtual void print();
	virtual int executeFunction(value_v_base *v1, value_v_base *v2, operType ot);
	friend void type_promote(value_v *v1, valueType newtype);
	friend void typeAnalysis(value_v *v1, value_v *v2, value_v *res);
	friend void plus_val(value_v *v1, value_v *v2, value_v *res);
	friend void minus_val(value_v *v1, value_v *v2, value_v *res);
	friend void multiply_val(value_v *v1, value_v *v2, value_v *res);
	friend void division_val(value_v *v1, value_v *v2, value_v *res);
public:
	int ival;
	double dval;
	string sval;
	valueType theType;
};

