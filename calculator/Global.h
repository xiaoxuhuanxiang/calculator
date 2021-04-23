#pragma once
#include <map>
using namespace std;
enum valueType
{
	VAL_INT,
	VAL_DOUBLE,
	VAL_STRING
};

enum operType
{
	OPER_PLUS,
	OPER_MINUS,
	OPER_MUL,
	OPER_DIV,
	OPER_LPTH,  //左括号
	OPER_RPTH,  //左括号
	OPER_NUM
};

const int doubleValidNum = 15;

class Global
{
public:
	Global();
	~Global();
	static void Init();
	static operType getOperType(const string &oper_c, int &len); //获取字符串对应的操作符类型，len表示匹配到的操作符长度（未来可能>1）
	static int getOperPrior_char(const string &oper_c);
	static int getOperPrior_type(operType theType);
	static bool isPartOfNumber(const char val_c, const char *val_c_reverse1);
	static int getMaxOperByte();    //获取运算符最大字节数，以考虑后续出现"**"这类符号
private:
	static map<string, operType> operMap;
	static int operPrior[OPER_NUM];
	static bool bInit;
	//vector<> operMap;
};

