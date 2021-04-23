// Extremely simple, stream client example.简单的客户端示例
// Works in conjunction with Server.cpp.与Server.cpp协同工作
// The program attempts to connect to the server and port specified on the command line. 程序尝试连接到命令行中指定的服务器和端口。
// The Server program prints the needed information when it is started. Once connected,the program sends data to the server, waits for a response and then exits. 服务器程序在启动时打印所需的信息。连接后，程序将向服务器发送数据，等待响应，然后退出。
// Compile and link with wsock32.lib. 编译并链接到wsock32.lib #pragma comment(lib,” wsock32.lib”)
// Pass the server name and port number on the command line. 在命令行上传递服务器名称和端口号。
// Example: Client MyMachineName 2000连接端口2000，我的主机名字是sc-PC
#pragma comment(lib,"wsock32.lib")
#include <stdio.h>   //标准输入输出头文件
#include <winsock.h> //相对于Winsock2.h的老版本
#include <string.h>  //string类
// Function prototype声明协议函数
void StreamClient(char* szServer, short nPort);
// Helper macro for displaying errors辅助宏显示错误
//使用 WSAGetLastError() 函数 来获得上一次的错误代码,为了提供和将来的多线程环境相兼容。
#define PRINTERROR(s) fprintf(stderr, "\n%: %d\n", s, WSAGetLastError())        //函数printerror()功能:系统返回提示信息，例如添加信息跳转提示

void main(int argc, char** argv)
{
    WORD wVersionRequested = MAKEWORD(1, 1); //wVersionRequested是Windows Sockets API提供的调用方可使用的最高版本号，MAKEWORD(1, 1)第一个参数为低位字节；第二个参数为高位字节
    WSADATA wsaData;                         //定义结构体变量wsaData
    int nRet;
    short nPort;
    //检查主机和端口参数
    if (argc != 3)
    {
        fprintf(stderr, "\nSyntax: client ServerName PortNumber\n"); //fprintf()函数根据指定的format(格式)发送信息(参数)到由stream(流)指定的文件
        return;
    }
    nPort = atoi(argv[2]);
    //对WinSock进行初始化并检查版本
    nRet = WSAStartup(wVersionRequested, &wsaData); //WSAStartup()函数向操作系统说明要用哪个库文件,因此就可以将库文件与当前的应用程序绑定，从而调用该版本的socket的各种函数,WSAStartup()进行相应的socket库绑定。
    if (wsaData.wVersion != wVersionRequested)      //wVersionRequested 要使用的 Windows Sockets API 版本
    {
        fprintf(stderr, "\n Wrong version\n"); // fprintf()函数根据指定的format(格式)发送信息(参数)到由stream(流)指定的文件
        return;
    }
    StreamClient(argv[1], nPort);
    //释放WinSock
    WSACleanup();
}
void StreamClient(char* szServer, short nPort) //创建客户流
{
    printf("\nStream Client connecting to server: %s on port: %d",
        szServer, nPort);
    //找服务器
    LPHOSTENT lpHostEntry;
    lpHostEntry = gethostbyname(szServer); // gethostbyname()函数用域名或者主机名获取地址，操作系统提供的库函数
    if (lpHostEntry == NULL)
    {
        PRINTERROR("gethostbyname()"); //printerror()功能：系统返回提示信息，这里是返回提示：gethostbyname()
        return;
    }
    //创建TCP/IP流套接字
    SOCKET theSocket;
    theSocket = socket(AF_INET,      // 地址族
        SOCK_STREAM,  //sock_stream对应于TCP协议，SOCK_DGRAM对应UDP协议，SOCK_RAW对应原始Socket
        IPPROTO_TCP); //参数protocol用来指定socket所使用的传输协议编号
    if (theSocket == INVALID_SOCKET)
    {
        PRINTERROR("socket()"); //返回提示：socket()
        return;
    }
    SOCKADDR_IN saServer;
    saServer.sin_family = AF_INET; // 选择 AF_INET 的目的就是使用 IPv4 进行通信。IPv4 使用 32 位地址，相比 IPv6 的 128 位来说，计算更快，便于用于局域网通信。
    saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
    // ^服务器的地址
    saServer.sin_port = htons(nPort); //命令行中的端口号
    //连接服务器
    int nRet;
    nRet = connect(theSocket,                //第一个参数：创建的套接字
        (LPSOCKADDR)&saServer,    // Server address第二个参数：要链接的服务器地址
        sizeof(struct sockaddr)); //第三个参数：服务器地址的长度
    if (nRet == SOCKET_ERROR)
    {
        PRINTERROR("socket()"); //返回提示：socket()
        closesocket(theSocket); //释放套接字
        return;
    }
    bool alwaysConnect = true;
    while (alwaysConnect)
    {
        char szBuf[256];
        printf("\nplease input your message:");
        scanf_s("%[^\n]%*c", szBuf);
        if (!strcmp(szBuf, "close"))
        {
            alwaysConnect = false;
        }

        nRet = send(theSocket,     //连接的套接字
            szBuf,         //数据缓冲区
            strlen(szBuf), //数据长度
            0);            // Flags
        if (nRet == SOCKET_ERROR)
        {
            PRINTERROR("send()");   //返回提示：send()
            closesocket(theSocket); //释放套接字
            return;
        }
        //等待回应
        nRet = recv(theSocket,     //第一个参数：本机创建的套接字
            szBuf,         // Receive buffer第二个参数：接受消息的字符串
            sizeof(szBuf), // Size of receive buffer第三个参数：允许接收字符串的最大长度
            0);            // Flags第四个参数：会对函数行为产生影响，一般设置为0
        if (nRet == SOCKET_ERROR)
        {
            PRINTERROR("recv()");   //返回提示：recv()
            closesocket(theSocket); //释放套接字
            return;
        }

        //
        // 显示接收到的数据
        //
        printf("\nData received: %s", szBuf);
    }

    closesocket(theSocket); //释放套接字
    return;
}
