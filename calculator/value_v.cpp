#include "value_v.h"
#include "value_c.h"
#include <iostream>
using namespace std;


value_v::value_v() :ival(0), dval(0), theType(VAL_INT)
{

}
value_v::~value_v()
{

}

void type_promote(value_v *v1, valueType newtype)
{
	if (v1->theType >= newtype) return;
	if (v1->theType == VAL_INT)
	{
		if (newtype == VAL_DOUBLE)
		{
			v1->dval = v1->ival;	
		}
		else if (newtype == VAL_STRING)
		{
			v1->sval = to_string(v1->ival);
		}
		v1->ival = 0;
	}
	else if (v1->theType == VAL_DOUBLE)
	{
		v1->sval = to_string(v1->dval);
		v1->dval = 0;
	}
	v1->theType = newtype;
}
//string类型并未真正使用，此处的类型分析提升函数与四则运算函数，若要支持大数，还需要扩展。
void typeAnalysis(value_v *v1, value_v *v2, value_v *res)
{
	res->theType = (v1->theType > v2->theType ? v1->theType: v2->theType);
	type_promote(v1, res->theType);
	type_promote(v2, res->theType);
}
void plus_val(value_v *v1, value_v *v2, value_v *res)
{
	typeAnalysis(v1, v2, res);
	if (res->theType != VAL_STRING)
	{
		res->ival = v1->ival + v2->ival;
		res->dval = v1->dval + v2->dval;
	}
	else
	{

	}
}
void minus_val(value_v *v1, value_v *v2, value_v *res)
{
	typeAnalysis(v1, v2, res);
	if (res->theType != VAL_STRING)
	{
		res->ival = v1->ival - v2->ival;
		res->dval = v1->dval - v2->dval;
	}
	else
	{

	}
}
void multiply_val(value_v *v1, value_v *v2, value_v *res)
{
	typeAnalysis(v1, v2, res);
	if (res->theType != VAL_STRING)
	{
		res->ival = v1->ival * v2->ival;
		res->dval = v1->dval * v2->dval;
	}
	else
	{

	}
}
void division_val(value_v *v1, value_v *v2, value_v *res)
{
	typeAnalysis(v1, v2, res);
	if (v1->theType == VAL_INT)
	{
		if (v1->ival%v2->ival != 0)
		{
			type_promote(v1, VAL_DOUBLE);
			type_promote(v2, VAL_DOUBLE);
			type_promote(res, VAL_DOUBLE);
		}
	}
	if (res->theType == VAL_INT)
	{
		if (v2->ival != 0)
		{
			res->ival = v1->ival / v2->ival;
		}
		else
		{
			cout << "error! divison by 0, ignore" << endl;
		}
	}
	else if (res->theType == VAL_DOUBLE)
	{
		if (v2->dval != 0)
		{
			res->dval = v1->dval / v2->dval;
		}
		else
		{
			cout << "error! divison by 0, ignore" << endl;
		}
	}
	else
	{

	}
}

int value_v::Init(value_c *vc)
{
	this->reset();
	const char *data = vc->getData();
	if (data == NULL) return -1;
	this->theType = vc->getValueType();
	switch (this->theType)
	{
	case VAL_INT:
		this->ival = atoi(data);
		break;
	case VAL_DOUBLE:
		this->dval = atof(data);
		break;
	case VAL_STRING:
		this->sval.append(data);
		break;
	}
	return 0;
}

void value_v::reset()
{
	ival = 0;
	dval = 0;
	sval.clear();
	theType = VAL_INT;
}

int value_v::executeFunction(value_v_base *v1, value_v_base *v2, operType ot)
{
	value_v *v1_v = NULL;
	value_v *v2_v = NULL;
	if (!(v1_v = dynamic_cast<value_v *>(v1)))
	{
		std::cout << "type is not compatible" << endl;
		return -1;
	}
	if (!(v2_v = dynamic_cast<value_v *>(v2)))
	{
		std::cout << "type is not compatible" << endl;
		return -2;
	}
	//注意由于采用出栈的方式计算，先进后出，所以操作数顺序要交换
	switch (ot)
	{
	case OPER_PLUS:
		plus_val(v2_v, v1_v, this);
		break;
	case OPER_MINUS:
		minus_val(v2_v, v1_v, this);
		break;
	case OPER_MUL:
		multiply_val(v2_v, v1_v, this);
		break;
	case OPER_DIV:
		division_val(v2_v, v1_v, this);
		break;
	default:
		break;
	}
	return 0;
}

void value_v::print()
{
	switch (theType)
	{
	case VAL_INT:
		cout << ival << endl;
		break;
	case VAL_DOUBLE:
		cout << dval << endl;
		break;
	case VAL_STRING:
		cout << sval << endl;
		break;
	default:
		break;
	}
}
/*oper value_v::getFunction(operType ot)
{
	if (bInit == false)
	{
		value_v::operFunc[OPER_PLUS] = plus_val;
		value_v::operFunc[OPER_MINUS] = minus_val;
		value_v::operFunc[OPER_MUL] = mutiply_val;
		value_v::operFunc[OPER_DIV] = division_val;
		value_v::operFunc[OPER_LPTH] = 0;
		value_v::operFunc[OPER_RPTH] = 0;
		bInit = true;
	}
	return operFunc[ot];
}*/