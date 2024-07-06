#include "pch.h"
#include "SERVERSOCKET.H"

CSerSocket::CSerSocket()
{
	if (InitSockEnv() == FALSE)
	{
		MessageBox(NULL, _T("�޷���ʼ���׽���"), _T("��ʼ���׽��ִ���"), MB_OK | MB_ICONERROR);
		exit(0);
	}
}

CSerSocket::~CSerSocket()
{
	WSACleanup();
}

BOOL CSerSocket::InitSockEnv()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(1, 1), &data) != 0)
		return FALSE;
	return TRUE;
}
