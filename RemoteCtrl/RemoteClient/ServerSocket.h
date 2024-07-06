#include "pch.h"
#include "framework.h"

class CSerSocket
{
public:

private:
	CSerSocket& operator=(const CSerSocket& ss);
	CSerSocket();
	~CSerSocket();
	BOOL InitSockEnv();
};

extern CSerSocket sock;