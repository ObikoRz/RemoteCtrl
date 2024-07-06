#pragma once
#include "pch.h"
#include "framework.h"

class CServerSocket
{
public:
	static CServerSocket* getInstance();
	bool InitSocket();
	bool AcceptClient();
	int DealCommand();
	bool Send(const char* pData, size_t nSize);
private:
	SOCKET m_sock;
	SOCKET m_client;
	CServerSocket& operator=(const CServerSocket&ss);
	CServerSocket();
	~CServerSocket();
	BOOL InitSockEnv();
	static CServerSocket* m_instance;
	static void releaseInstance();

	class CHelper
	{
		public:
			CHelper();
			~CHelper();
		private:

	};

	static CHelper m_help;
};

