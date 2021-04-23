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
	OPER_LPTH,  //������
	OPER_RPTH,  //������
	OPER_NUM
};

const int doubleValidNum = 15;

class Global
{
public:
	Global();
	~Global();
	static void Init();
	static operType getOperType(const string &oper_c, int &len); //��ȡ�ַ�����Ӧ�Ĳ��������ͣ�len��ʾƥ�䵽�Ĳ��������ȣ�δ������>1��
	static int getOperPrior_char(const string &oper_c);
	static int getOperPrior_type(operType theType);
	static bool isPartOfNumber(const char val_c, const char *val_c_reverse1);
	static int getMaxOperByte();    //��ȡ���������ֽ������Կ��Ǻ�������"**"�������
private:
	static map<string, operType> operMap;
	static int operPrior[OPER_NUM];
	static bool bInit;
	//vector<> operMap;
};

