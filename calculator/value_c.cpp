#include "value_c.h"
#include <algorithm>

value_c::value_c():m_bOper(false), m_bdot(false),m_validNum(0), m_pos(0)
{
}

value_c::~value_c()
{

}

int value_c::Init(string &input, int pos, bool isOper)
{
	m_data = input;
	m_pos = pos;
	m_bOper = isOper;
	if (isOper)
	{
		int len;
		m_operType = Global::getOperType(m_data, len);
		if (m_operType == OPER_NUM) return -1;
		return 0;
	}
	
	if (!isValid())
	{
		m_data.clear();
		return -1;
	}
	removeZeroFirst();
	m_validNum = calcuValidNum();

	if (m_validNum > doubleValidNum) //有效位数 > 15，需要string计算
	{
		m_valueType = VAL_STRING;
	}
	else if (m_bdot == false) //无小数点，整数
	{
		m_valueType = VAL_INT;
	}
	else //if (m_bdot == true) 有小数点，double
	{
		m_valueType = VAL_DOUBLE;
	}
	return 0;
}
int value_c::getValidNum()
{
	return m_validNum;
}

const char* value_c::getData()
{
	return m_data.c_str();
}

int value_c::getPos()
{
	return m_pos;
}
bool value_c::isValid()
{
	if (m_data.size() <= 0) return false;
	int dotNum = 0;
	for (string::iterator it = m_data.begin(); it != m_data.end(); ++it)
	{
		if (*it == '.')
		{
			if (it == m_data.begin()) return false;
			++dotNum;
		}
		else if (*it >= '0' && *it <= '9')
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	if(dotNum == 1) m_bdot = true;
	return (dotNum == 1 || dotNum == 0);
}

void value_c::removeZeroFirst()
{
	if (m_data.size() <= 0) return;
	string::iterator it;
	if (m_data[0] == '-')
	{
		it = m_data.begin() + 1;
	}
	else
	{
		it = m_data.begin();
	}
	string::iterator itStart = it;
	string::iterator itEnd = it;
	for (; it != m_data.end(); ++it)
	{
		if (*it == '0')
		{
			++itEnd;
		}
		else if(*it == '.')
		{
			--itEnd;
			break;
		}
		else
		{
			break;
		}
	}

	if(itEnd > itStart) m_data.erase(itStart, itEnd);
}

bool value_c::isOper()
{
	return m_bOper;
}

int value_c::calcuValidNum()
{
	if (!m_bdot) return m_data.size();
	int dotPos = -1;
	int firstNonZeroPos = -1;
	for (string::iterator it = m_data.begin(); it != m_data.end(); ++it)
	{
		if (dotPos != -1 && firstNonZeroPos != -1) break;
		if (*it == '.')
		{
			dotPos = int(it - m_data.begin());
		}
		else if (*it > '0' && *it <= '9')
		{
			if(firstNonZeroPos == -1) firstNonZeroPos = int(it - m_data.begin());
		}
	}

	if (firstNonZeroPos > dotPos) return m_data.size() - firstNonZeroPos;
	else return m_data.size() - firstNonZeroPos - 1;
	return 0;
}

valueType value_c::getValueType()
{
	return m_valueType;
}

operType value_c::getOperType()
{
	return m_operType;
}