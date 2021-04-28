#pragma once
#include <string>

const std::string quitIden = "quit"; //ÍË³öÓï¾ä
const std::string promptIden = ">";  //ÃüÁîÌáÊ¾·û
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

