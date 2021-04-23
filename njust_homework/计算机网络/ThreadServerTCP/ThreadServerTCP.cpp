// socket通信  服务器
//TCP：在客户端和服务器之间提供可靠的字节流传输（“管道”）
//#include "stdafx.h" //stdafx.h中没有函数库，只是定义一些环境参数，使编译出来的程序能在32位的操作系统环境下工作
#pragma comment(lib, "ws2_32.lib")//连接Winsock2.h的静态库文件
#include <Winsock2.h>//winsock第2版的头文件，里面有多种函数可以帮助使用Winsock
#include <WS2tcpip.h>//设置或获取套接字选项
#include <stdio.h>//标准输入输出头文件
#include <string.h>//包含一些常用的C字符串处理函数
#include <stdlib.h>//包含了C语言的一些常用库函数
#include <thread>//声明std::thread线程类
#include <iostream>//表示输入输出流
void func(SOCKET arg, SOCKADDR_IN client_addr, int pos)// socket编程, SOCKADDR_IN 是声明套接字类型
{
    char recvBuf[128];//接收的字符串 接收Buf,，设置长度为128
    char sendBuf[128];//发送的字符串 发送Buf，设置长度为128
    char tempBuf[256];//临时字符串，设置长度为256
    int sockConn = arg;
    while (true)
    {
        //从客户端接收消息
        printf("wait receive client message :\n");//输出“等待接收客户端的消息”
        recv(sockConn, recvBuf, 128, 0);//
        // 第一个参数：本机创建的套接字
        // 第二个参数：接收的字符串
        // 第三个参数：接收的字符串长度
        // 第四个参数：会对函数行为产生影响，一般设置为0
        //解析客户端地址信息
        char ipClient[16];//客户IP字符串，设置长度为16
        inet_ntop(AF_INET, &client_addr.sin_addr, ipClient, sizeof(ipClient));//第一个参数指定地址族，对于TCP/IP协议的套接字，地址族为AF_INET；第二个参数指向套接字的IP地址（sin_addr）；第三个参数是用户IP；第四个参数是用户IP地址的大小。
        printf("%s said: %s\n", ipClient, recvBuf);//输出“用户IP said: 接收字符串”
        //向客户端发送消息
        gets_s(sendBuf);
        send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);// 
        // 第一个参数：本机创建的套接字
        // 第二个参数：要发送的字符串
        // 第三个参数：发送字符串长度
        // 第四个参数：会对函数行为产生影响，一般设置为0
    }
}
int main()
{
    std::cout << "Hello World!\n";//使用std::是在调用标准命名空间，输出“Hello World!”
/*
WSAStartup必须是应用程序或DLL调用的第一个Windows Sockets函数。
它允许应用程序或DLL指明Windows Sockets API的版本号及获得特定Windows Sockets实现的细节。
应用程序或DLL只能在一次成功的WSAStartup()调用之后才能调用进一步的Windows Sockets API函数。
*/
    WORD wVersionRequested;// wVersionRequested是Windows Sockets API提供的调用方可使用的最高版本号
    WSADATA wsaData;// 定义结构体变量wsaData, 用来存储被WSAStartup函数调用后返回的Windows Sockets数据
    int err;//定义整型变量err
    wVersionRequested = MAKEWORD(1, 1);//第一个参数为低位字节；第二个参数为高位字节
    err = WSAStartup(wVersionRequested, &wsaData);//对winsock进行初始化，加载一个Winsock库版本
    if (err != 0) { return 0; }
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE（）取得16进制数最低位；HIBYTE（）取得16进制数最高那个字节的内容
    {
        WSACleanup();//在一个多线程的环境下，WSACleanup（）中止了Windows Sockets在所有线程上的操作。
        return 0;
    }//进行版本检查
    // 申请存储线程的数组
    std::thread threads[10];//使用std的thread创建一个线程对象
    int thread_num = 0;//先记线程个数为0
    /*socket通讯*/
    //申请套接字
    SOCKET Svr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建SOCKET对象Svr,AF_INET指IPV4版本, 第一个参数表示ip协议族，第二个参数表示数据流方式，第三个参数是TCP协议。
    SOCKADDR_IN addr;//定义存放本地地址信息的结构体变量addr
    //要绑定的基础信息
    addr.sin_family = AF_INET;//sin_family指协议族，一般是AF_INET,表示采用ipv4协议
    addr.sin_port = htons(6002);//将端口号（6002）赋给sin_port, htons 将整型类型转换成网络字节序
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htonl将长整型转换成网络字节序
    //进行绑定
    int len = sizeof(sockaddr);
    bind(Svr, (struct sockaddr*) & addr, len);//指定名字、类型、长度
    //监听套接字
    int ret = listen(Svr, 10); //第一个参数：要监听的socket（套接字）,第二个参数：等待连接队列的最大长度
    if (ret == SOCKET_ERROR)//若发生错误
    {
        printf("侦听失败\n");
        closesocket(Svr);//释放套接字Svr
    }
    //存储请求连接的套接字信息
    SOCKADDR_IN addrClient;
    while (true)
    {
        //接受连接，返回一个socket
        SOCKET sockConn = accept(Svr, (struct sockaddr*) & addrClient, &len);
        if (sockConn == INVALID_SOCKET)
        {
            //printf("无效socket\n");
            continue;
        }
        //将通讯细节放在线程里处理
        threads[thread_num] = std::thread(func, sockConn, addrClient, thread_num);
        thread_num++;
        if (thread_num == 5)
        {
            printf("线程池达到数量上限");
        }
    }
    //等待线程结束
    for (int i = 0; i < thread_num; i++)
        threads[i].join();
    //释放套接字
    closesocket(Svr);
    WSACleanup();//终止对套接字库的使用
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
