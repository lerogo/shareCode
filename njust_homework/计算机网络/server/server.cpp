// Server.cpp
// Extremely simple, stream server example. 简单的服务器示例
// Works in conjunction with Client.cpp. 与Client.cpp协同工作。
// The program sets itself up as a server using the TCP设置为使用TCP的服务器
//等待来自客户机的数据，显示传入的数据，向客户端发送消息，然后退出。
// protoocl. It waits for data from a client, displayss
// the incoming data, sends a message back to the client
// and then exits.
//	编译并链接到wsock32.lib #pragma comment(lib,” wsock32.lib”)s
// Compile and link with wsock32.lib
//
// Pass the port number that the server should bind() to
// on the command line. Any port number not already in use
// can be specified.
//
// Example: Server 2000	以端口号2000为例
//

//lib 文件
#pragma comment(lib,"wsock32.lib")

//头文件
#include <stdio.h>//标准输入输出头文件
#include <winsock.h>//相对于Winsock2.h的老版本
#include <string.h>//字符串
#include <iostream>

// Function prototype
//函数声明
void StreamServer(short nPort);

// Helper macro for displaying errors
//输出error辅助宏显示错误
#define PRINTERROR(s) fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())
//函数是socket编程时需要用到的一个函数，使用 WSAGetLastError() 函数来获得上一次的错误代码,而不是依靠全局错误变量, 是为了提供和将来的多线程环境相兼容。

/////////////////////////////////////////////////////////

void main(int argc, char** argv)
{
    //变量声明
    //高位字节指明副版本、低位字节指明主版本
    WORD wVersionRequested = MAKEWORD(1, 1);        //SDK这个宏创建一个无符号16位整型，通过连接两个给定的无符号参数。
    WSADATA wsaData;                                //定义结构体变量wsaData
    int nRet;                                       //状态
    short nPort;                                    // 端口 port

    //
    // Check for port argument
    //
    //参数不够
    if (argc != 2)
    {
        //输出流
        fprintf(stderr, "\nSyntax: server PortNumber\n");
        return;
    }

    nPort = atoi(argv[1]);  //获取port atoi字符转int

    //
    // Initialize WinSock and check version
    //
    nRet = WSAStartup(wVersionRequested, &wsaData); //初始化连接
    //初始化错误
    if (wsaData.wVersion != wVersionRequested)
    {
        fprintf(stderr, "\n Wrong version\n");
        return;
    }
    // Do the stuff a stream server does
    StreamServer(nPort);

    // Release WinSock
    // 结束  释放
    WSACleanup();
}

////////////////////////////////////////////////////////////

void StreamServer(short nPort)
{
    //
    // Create a TCP/IP stream socket to "listen" with
    // 创建 TCP/IP 监听
    SOCKET  listenSocket;

    listenSocket = socket(AF_INET,          // IPv4
        SOCK_STREAM,        // TCP
        IPPROTO_TCP);       // TCP
    //创建成功与否
    if (listenSocket == INVALID_SOCKET)
    {
        PRINTERROR("socket()");
        return;
    }

    //
    // Fill in the address structure
    //
    SOCKADDR_IN saServer;// 定义存放本地地址信息的结构体变量addrSrv，存放本地地址信息

    saServer.sin_family = AF_INET;// sin_family指代协议族，其值一般是AF_INET表示采用IPv4协议
    saServer.sin_addr.s_addr = INADDR_ANY;  // 响应所有地址
    saServer.sin_port = htons(nPort);       //将端口号赋给sin_port ，htons()就是将一个数的高低位互换

    //
    // bind the name to the socket
    //
    int nRet;
    // 将listenSocket绑定到相应端口(nPort)上。绑定未必成功，如无错误发生，则bind()返回0。否则的话，将返回 - 1。
    nRet = bind(listenSocket,               // Socket 
        (LPSOCKADDR)&saServer,      // Our address
        sizeof(struct sockaddr));   // Size of address structure
    //错误判断
    if (nRet == SOCKET_ERROR)
    {
        PRINTERROR("bind()");
        closesocket(listenSocket);
        return;
    }

    //
    // This isn't normally done or required, but in this 
    // example we're printing out where the server is waiting
    // so that you can connect the example client.
    //

    //打印server 让client找到

    int nLen;
    nLen = sizeof(SOCKADDR);
    char szBuf[256];
    //获取计算机名字
    nRet = gethostname(szBuf, sizeof(szBuf));
    if (nRet == SOCKET_ERROR)
    {
        PRINTERROR("gethostname()");
        closesocket(listenSocket);
        return;
    }

    //
    // Show the server name and port number
    // 打印server名字（主机名）
    printf("\nServer named %s waiting on port %d\n",
        szBuf, nPort);

    //
    // Set the socket to listen
    //

    printf("\nlisten()");
    // 监听
    nRet = listen(listenSocket,                 // Bound socket绑定socket
        SOMAXCONN);                             // Number of connection request queue队列数（5）
    if (nRet == SOCKET_ERROR)
    {
        PRINTERROR("listen()");
        closesocket(listenSocket);
        return;
    }

    //
        // Wait for an incoming request
        //
    SOCKET  remoteSocket;

    printf("\nBlocking at accept()");
    //在一个套接口接受的一个连接
    remoteSocket = accept(listenSocket,         // Listening socket
        NULL,                                   // Optional client address
        NULL);
    if (remoteSocket == INVALID_SOCKET)
    {
        PRINTERROR("accept()");
        closesocket(listenSocket);
        return;
    }
    bool alwaysAccept = true;
    while (alwaysAccept) {
        //
        // We're connected to a client
        // New socket descriptor returned already
        // has clients address

        //
        // Receive data from the client
        //
        //从TCP连接的另一端接收数据。
        memset(szBuf, 0, sizeof(szBuf));
        nRet = recv(remoteSocket,           // Connected client 指定接收端套接字描述符
            szBuf,                          // Receive buffer 指明一个缓冲区，该缓冲区用来存放recv函数接收到的数据；
            sizeof(szBuf),                  // Lenght of buffer 指明buf的长度；
            0);                             // Flags
        if (nRet == INVALID_SOCKET)
        {
            PRINTERROR("recv()");
            closesocket(listenSocket);
            closesocket(remoteSocket);
            return;
        }
        if (!strcmp(szBuf, "close")) {
            alwaysAccept = false;
        }
        //
        // Display received data
        //
        printf("\nData received: %s", szBuf);
        //提供服务
        //
        // Send data back to the client
        //
        strcpy_s(szBuf, "From the Server");
        //向TCP连接的另一端发送数据。
        nRet = send(remoteSocket,               // Connected socket     指定发送端套接字描述符；
            szBuf,                      // Data buffer                  存放应用程序要发送数据的缓冲区；
            strlen(szBuf),              // Lenght of data               实际要发送的数据的字节数；
            0);                         // Flags

    }
    //
    // Close BOTH sockets before exiting
    // 关闭
    closesocket(remoteSocket);
    closesocket(listenSocket);
    return;
}
