#include "Client.h"
#include <string>
#include <iostream>
#include "Executor.h"
#include "Executor_RPN.h"
#include "value_v_base.h"
#include "value_v.h"
using namespace std;
Client::Client()
{

}

Client::~Client()
{

}

void Client::clientRun()
{
	string str_crt = "";
	bool lastExecute = false;
	int res(0);
	while (1)
	{
		size_t pos = str_crt.find(sentenceEnd);
		if (!str_crt.empty() && lastExecute)
		{
			if (pos == str_crt.npos)
			{
				cout << promptIden << str_crt << endl;
			}
		}
		
		if (pos == str_crt.npos)
		{
			string tmp;
			cout << promptIden;
			getline(cin, tmp);
			str_crt += tmp;
			lastExecute = false;
			continue;
		}
		else
		{
			string str(str_crt.begin(), str_crt.begin() + pos);
			str_crt.erase(str_crt.begin(), str_crt.begin() + pos + 1);
			cout << "Full input detected: " << str << endl;
			res = runOneSentence(str);
			if (res == RES_QUIT) break;
			lastExecute = true;
		}
	}
}

int Client::runOneSentence(string &oneStc)
{
	if (oneStc == quitIden) return RES_QUIT;
	Executor *p = new Executor_RPN();
	p->setInput(oneStc);
	if (p->execute())
	{
		delete p;
		return RES_ERROR;
	}
	value_v_base *res = p->getResult();
	cout << "theResult" << "=";
	res->print();
	delete p;
	return RES_OK;
}