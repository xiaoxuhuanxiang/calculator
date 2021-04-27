#pragma once
#include <string>

const std::string quitIden = "quit";
class Client
{
public:
	Client();
	~Client();
	void clientRun();
private:
	enum runRes {
		RES_OK,
		RES_ERROR,
		RES_QUIT
	};
	int runOneSentence(std::string &oneStc);
};

