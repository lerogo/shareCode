//socket通信  客户端
//TCP：在客户端和服务器之间提供可靠的字节流传输（“管道”）
//#include "stdafx.h"//stdafx.h中没有函数库，只是定义一些环境参数，使编译出来的程序能在32位的操作系统环境下工作
#pragma comment(lib, "ws2_32.lib")//连接Winsock2.h的静态库文件
#include <Winsock2.h>//winsock第2版的头文件，里面有多种函数可以帮助使用Winsock
#include <WS2tcpip.h>//设置或获取套接字选项
#include <stdio.h>//标准输入输出头文件
#include <string.h>//包含一些常用的C字符串处理函数
#include <stdlib.h>//包含了C语言的一些常用库函数
#include <thread>//声明std::thread线程类
#include <iostream>//表示输入输出流
void new_client(int pos)
{
    WORD wVersionRequested;//wVersionRequested是Windows Sockets API提供的调用方可使用的最高版本号
    WSADATA wsaData;//定义结构体变量wsaData
    int err;//定义整型变量err
    wVersionRequested = MAKEWORD(1, 1);//第一个参数为低位字节；第二个参数为高位字节
    err = WSAStartup(wVersionRequested, &wsaData);//对winsock进行初始化，加载一个Winsock库版本
    if (err != 0) { return; }
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE（）取得16进制数最低位；HIBYTE（）取得16进制数最高那个字节的内容
    {
        WSACleanup();//在一个多线程的环境下，WSACleanup（）中止了Windows Sockets在所有线程上的操作。
        return;
    }
    SOCKET Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//第一个参数表示ip协议族，第二个参数表示数据流方式，第三个参数是TCP协议
    SOCKADDR_IN Server;//定义存放本地地址信息的结构体变量Server
    // 要连接的基础信息
    Server.sin_family = AF_INET;//sin_family指协议族，一般是AF_INET,表示采用ipv4协议
    Server.sin_port = htons(6002);//将端口号（6002）赋给sin_port, htons 将整型类型转换成网络字节序
    inet_pton(AF_INET, "127.0.0.1", &Server.sin_addr); //点分十进制地址转换成网络字节序
    // 向服务端发起连接
    int ret = connect(Client, (struct sockaddr*) & Server, sizeof(Server));//
        //第一个参数：创建的套接字
        //第二个参数：要链接的套接字地址
        //第三个参数：单位长度
    if (ret == SOCKET_ERROR)
    {
        printf("连接失败\n");
        closesocket(Client);//释放套接字Client
        WSACleanup();//终止对套接字库的使用
        return;
    }
    char recvBuf[128];//接收字符串，设置长度为128
    char sendBuf[128];//发送字符串，设置长度为128
    while (true)
    {
        printf("please input message:\n");//输出“请输入信息：”
        gets_s(sendBuf);//得到输出字符串
        sprintf_s(sendBuf, "%s_%d", sendBuf, pos);
        send(Client, sendBuf, strlen(sendBuf) + 1, 0);//
        // 第一个参数：本机创建的套接字
        // 第二个参数：要发送的字符串
        // 第三个参数：发送字符串长度
        // 第四个参数：会对函数行为产生影响，一般设置为0
        recv(Client, recvBuf, 128, 0);//
        // 第一个参数：本机创建的套接字
        // 第二个参数：接受消息的字符串
        // 第三个参数：允许接收字符串的最大长度
        // 第四个参数：会对函数行为产生影响，一般设置为0
        char ipServer[16];//服务器方的IP，设置大小为16字节
        inet_ntop(AF_INET, &Server.sin_addr, ipServer, sizeof(ipServer));//第一个参数指定地址族为AF_INET；第二个参数指向套接字的IP地址（sin_addr）；第三个参数是服务器IP；第四个参数是服务器IP地址的大小
        printf("%s said: %s\n", ipServer, recvBuf);//输出“服务器IP said: 接收字符串”
    }
    closesocket(Client);//释放套接字
    WSACleanup();//终止对套接字库的使用
}
int main()
{
    std::cout << "Hello World!\n";//输出“Hello World!”
    std::thread threads[10];//建立线程对象
    int client_num = 5;
    for (int i = 0; i < client_num; i++)
        threads[i] = std::thread(new_client, i);
    for (int i = 0; i < client_num; i++)//等待线程结束
        threads[i].join();
    return 0;

}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
