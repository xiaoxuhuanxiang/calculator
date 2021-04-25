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
	int Init(string &input, int pos, bool isOper);  //��ʼ��
	bool isOper();									//�Ƿ��������
	int getValidNum();								//��ȡ��Ч����λ��
	valueType getValueType();						//��ȡ��ֵ����
	operType getOperType();							//��ȡ���������
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

