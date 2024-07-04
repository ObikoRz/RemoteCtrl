// RemoteCtrl.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "framework.h"
#include "RemoteCtrl.h"
#include "ServerSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // 初始化 MFC 并在失败时显示错误
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: 在此处为应用程序的行为编写代码。
            wprintf(L"错误: MFC 初始化失败\n");
            nRetCode = 1;
        }
        else
        {
            // TODO: 在此处为应用程序的行为编写代码。
            //初始化
            server;
            WSADATA data;
            WSAStartup(MAKEWORD(1, 1), &data);  //TODO：          返回值处理
            SOCKET serv_sock = socket(PF_INET, SOCK_STREAM, 0);   //TODO   校验
            sockaddr_in serv_addr;
            memset(&serv_addr, 0, sizeof(serv_addr));
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = INADDR_ANY;
            serv_addr.sin_port = htons(9999);
            //绑定
            bind(serv_sock, (sockaddr*)&serv_addr, sizeof(serv_addr)); //TODO  校验
            //监听
            listen(serv_sock, 1);
            char buf[1024];
            recv(serv_sock, buf, sizeof(buf), 0);
            send(serv_sock, buf, sizeof(buf), 0);

            closesocket(serv_sock);
            WSACleanup();
        }
    }
    else
    {
        // TODO: 更改错误代码以符合需要
        wprintf(L"错误: GetModuleHandle 失败\n");
        nRetCode = 1;
    }

    return nRetCode;
}
