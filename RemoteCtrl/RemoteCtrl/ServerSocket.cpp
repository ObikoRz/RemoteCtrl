#include "pch.h"
#include "ServerSocket.h"

CServerSocket* CServerSocket::m_instance = NULL;
CServerSocket::CHelper CServerSocket::m_help;
//CServerSocket* pserver = CServerSocket::getInstance();

CServerSocket* CServerSocket::getInstance()
{   //静态函数没有this指针，所以无法直接访问成员变量
	std::cout << m_instance << std::endl;
	if (m_instance == NULL)
		m_instance = new CServerSocket();
	return m_instance;
}

bool CServerSocket::InitSocket()
{
	if (m_sock == -1)	return false;
	sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(9999);
	//绑定
	if (bind(m_sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)	return false;
	//监听
	if(listen(m_sock, 1)== - 1) return false;
	return true;
}

bool CServerSocket::AcceptClient()
{
	sockaddr_in cli_addr;
	int cli_size = sizeof(cli_addr);
	SOCKET m_client = accept(m_sock, (sockaddr*)&cli_addr, &cli_size);
	if(m_client == -1)	return false;
	return true;
}

int CServerSocket::DealCommand()
{
	char buf[1024] = "";
	while (true)
	{
		int len = recv(m_client, buf, sizeof(buf), 0);
		if (len <= 0) {
			return -1;
		}
		//TODO 处理命令
	}
}

bool CServerSocket::Send(const char* pData, size_t nSize)
{
	if (m_client == -1)	return false;
	return send(m_client, pData, nSize, 0)>0;
}

CServerSocket& CServerSocket::operator=(const CServerSocket& ss)
{
	return *this;
}

CServerSocket::CServerSocket()
{
	if (InitSockEnv()==FALSE) {
		MessageBox(NULL, _T("无法初始化套接字，请检查网络设置！"), _T("初始化套接字错误！"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	SOCKET m_sock = socket(PF_INET, SOCK_STREAM, 0);
}

CServerSocket::~CServerSocket()
{
	std::cout << "-----------" << std::endl;
	closesocket(m_sock);
	WSACleanup();
}

BOOL CServerSocket::InitSockEnv()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
		return FALSE;
	return TRUE;
}

void CServerSocket::releaseInstance()
{
	if (m_instance) {
		CServerSocket* temp = m_instance;
		m_instance = NULL;
		delete temp;
	}
}

CServerSocket::CHelper::CHelper()
{
	getInstance();
}

CServerSocket::CHelper::~CHelper()
{
	releaseInstance();
}

