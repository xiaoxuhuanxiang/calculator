#pragma once
#include <string>
#include <set>
#include "Global.h"
using namespace std;
class value_c
{
public:
	value_c();
	~value_c();
	int Init(string &input, int pos, bool isOper);  //初始化
	bool isOper();									//是否是运算符
	int getValidNum();								//获取有效数字位数
	valueType getValueType();						//获取数值类型
	operType getOperType();							//获取运算符类型
	const char* getData();
	int getPos();
private:
	bool isValid();
	void removeZeroFirst();
	int calcuValidNum();
	bool m_bOper;
	bool m_bdot;
	string m_data;
	int m_validNum;
	valueType m_valueType;
	operType m_operType;
	set<string> m_oper_c;
	int m_pos;
};

