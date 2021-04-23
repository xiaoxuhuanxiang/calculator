#include "Executor.h"

Executor::Executor():m_theParser(0), m_res(0)
{

}
Executor::~Executor()
{
	while (!m_theQueue.empty())
	{
		value_c *p = m_theQueue.front();
		m_theQueue.pop();
		delete p;
	}
	if (m_theParser)
	{
		delete m_theParser;
	}
}