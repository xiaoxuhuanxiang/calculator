#include "Global.h"
map<string, operType> Global::operMap;
int Global::operPrior[OPER_NUM];
bool Global::bInit = false;
Global::Global()
{
}
Global::~Global()
{
}

void Global::Init()
{
	if (!bInit)
	{
		operMap["+"] = OPER_PLUS;
		operMap["-"] = OPER_MINUS;
		operMap["*"] = OPER_MUL;
		operMap["/"] = OPER_DIV;
		operMap["("] = OPER_LPTH;
		operMap[")"] = OPER_RPTH;
		operPrior[OPER_PLUS ] =  1;
		operPrior[OPER_MINUS] =  1;
		operPrior[OPER_MUL  ] =  2;
		operPrior[OPER_DIV  ] =  2;
		operPrior[OPER_LPTH ] = -1;
		operPrior[OPER_RPTH ] = -1;
		bInit = true;
	}
}

operType Global::getOperType(const string &oper_c, int &len)
{
	if (!bInit) Init();

	if (operMap.find(oper_c) != operMap.end())
	{
		len = int(oper_c.size());
		return operMap[oper_c];
	}
	string oper_c_tmp = oper_c;
	oper_c_tmp.pop_back();
	while (oper_c_tmp.size() > 0)
	{
		if (operMap.find(oper_c_tmp) != operMap.end())
		{
			len = int(oper_c_tmp.size());
			return operMap[oper_c_tmp];
		}
		else
		{
			oper_c_tmp.pop_back();
		}
	}
	len = 0;
	return OPER_NUM;  //用于表明找不到
}

int Global::getMaxOperByte()
{
	return 1;
}

bool Global::isPartOfNumber(const char val_c, const char *val_c_reverse1)
{
	if (val_c == '.') return true;
	if (val_c == '-' && val_c_reverse1==NULL) return true;
	if (val_c == '-' && !val_c_reverse1 && val_c_reverse1[0] == '(') return true;
	if (val_c >= '0' && val_c <= '9') return true;
	return false;
}

int Global::getOperPrior_char(const string &oper_c)
{
	if (operMap.find(oper_c) == operMap.end()) return -2;
	return getOperPrior_type(operMap[oper_c]);
}
int Global::getOperPrior_type(operType theType)
{
	return operPrior[theType];
}