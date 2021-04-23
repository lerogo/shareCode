// Server.cpp
// Extremely simple, stream server example. �򵥵ķ�����ʾ��
// Works in conjunction with Client.cpp. ��Client.cppЭͬ������
// The program sets itself up as a server using the TCP����Ϊʹ��TCP�ķ�����
//�ȴ����Կͻ��������ݣ���ʾ��������ݣ���ͻ��˷�����Ϣ��Ȼ���˳���
// protoocl. It waits for data from a client, displayss
// the incoming data, sends a message back to the client
// and then exits.
//	���벢���ӵ�wsock32.lib #pragma comment(lib,�� wsock32.lib��)s
// Compile and link with wsock32.lib
//
// Pass the port number that the server should bind() to
// on the command line. Any port number not already in use
// can be specified.
//
// Example: Server 2000	�Զ˿ں�2000Ϊ��
//

//lib �ļ�
#pragma comment(lib,"wsock32.lib")

//ͷ�ļ�
#include <stdio.h>//��׼�������ͷ�ļ�
#include <winsock.h>//�����Winsock2.h���ϰ汾
#include <string.h>//�ַ���
#include <iostream>

// Function prototype
//��������
void StreamServer(short nPort);

// Helper macro for displaying errors
//���error��������ʾ����
#define PRINTERROR(s) fprintf(stderr,"\n%: %d\n", s, WSAGetLastError())
//������socket���ʱ��Ҫ�õ���һ��������ʹ�� WSAGetLastError() �����������һ�εĴ������,����������ȫ�ִ������, ��Ϊ���ṩ�ͽ����Ķ��̻߳�������ݡ�

/////////////////////////////////////////////////////////

void main(int argc, char** argv)
{
    //��������
    //��λ�ֽ�ָ�����汾����λ�ֽ�ָ�����汾
    WORD wVersionRequested = MAKEWORD(1, 1);        //SDK����괴��һ���޷���16λ���ͣ�ͨ�����������������޷��Ų�����
    WSADATA wsaData;                                //����ṹ�����wsaData
    int nRet;                                       //״̬
    short nPort;                                    // �˿� port

    //
    // Check for port argument
    //
    //��������
    if (argc != 2)
    {
        //�����
        fprintf(stderr, "\nSyntax: server PortNumber\n");
        return;
    }

    nPort = atoi(argv[1]);  //��ȡport atoi�ַ�תint

    //
    // Initialize WinSock and check version
    //
    nRet = WSAStartup(wVersionRequested, &wsaData); //��ʼ������
    //��ʼ������
    if (wsaData.wVersion != wVersionRequested)
    {
        fprintf(stderr, "\n Wrong version\n");
        return;
    }
    // Do the stuff a stream server does
    StreamServer(nPort);

    // Release WinSock
    // ����  �ͷ�
    WSACleanup();
}

////////////////////////////////////////////////////////////

void StreamServer(short nPort)
{
    //
    // Create a TCP/IP stream socket to "listen" with
    // ���� TCP/IP ����
    SOCKET  listenSocket;

    listenSocket = socket(AF_INET,          // IPv4
        SOCK_STREAM,        // TCP
        IPPROTO_TCP);       // TCP
    //�����ɹ����
    if (listenSocket == INVALID_SOCKET)
    {
        PRINTERROR("socket()");
        return;
    }

    //
    // Fill in the address structure
    //
    SOCKADDR_IN saServer;// �����ű��ص�ַ��Ϣ�Ľṹ�����addrSrv����ű��ص�ַ��Ϣ

    saServer.sin_family = AF_INET;// sin_familyָ��Э���壬��ֵһ����AF_INET��ʾ����IPv4Э��
    saServer.sin_addr.s_addr = INADDR_ANY;  // ��Ӧ���е�ַ
    saServer.sin_port = htons(nPort);       //���˿ںŸ���sin_port ��htons()���ǽ�һ�����ĸߵ�λ����

    //
    // bind the name to the socket
    //
    int nRet;
    // ��listenSocket�󶨵���Ӧ�˿�(nPort)�ϡ���δ�سɹ������޴���������bind()����0������Ļ��������� - 1��
    nRet = bind(listenSocket,               // Socket 
        (LPSOCKADDR)&saServer,      // Our address
        sizeof(struct sockaddr));   // Size of address structure
    //�����ж�
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

    //��ӡserver ��client�ҵ�

    int nLen;
    nLen = sizeof(SOCKADDR);
    char szBuf[256];
    //��ȡ���������
    nRet = gethostname(szBuf, sizeof(szBuf));
    if (nRet == SOCKET_ERROR)
    {
        PRINTERROR("gethostname()");
        closesocket(listenSocket);
        return;
    }

    //
    // Show the server name and port number
    // ��ӡserver���֣���������
    printf("\nServer named %s waiting on port %d\n",
        szBuf, nPort);

    //
    // Set the socket to listen
    //

    printf("\nlisten()");
    // ����
    nRet = listen(listenSocket,                 // Bound socket��socket
        SOMAXCONN);                             // Number of connection request queue��������5��
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
    //��һ���׽ӿڽ��ܵ�һ������
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
        //��TCP���ӵ���һ�˽������ݡ�
        memset(szBuf, 0, sizeof(szBuf));
        nRet = recv(remoteSocket,           // Connected client ָ�����ն��׽���������
            szBuf,                          // Receive buffer ָ��һ�����������û������������recv�������յ������ݣ�
            sizeof(szBuf),                  // Lenght of buffer ָ��buf�ĳ��ȣ�
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
        //�ṩ����
        //
        // Send data back to the client
        //
        strcpy_s(szBuf, "From the Server");
        //��TCP���ӵ���һ�˷������ݡ�
        nRet = send(remoteSocket,               // Connected socket     ָ�����Ͷ��׽�����������
            szBuf,                      // Data buffer                  ���Ӧ�ó���Ҫ�������ݵĻ�������
            strlen(szBuf),              // Lenght of data               ʵ��Ҫ���͵����ݵ��ֽ�����
            0);                         // Flags

    }
    //
    // Close BOTH sockets before exiting
    // �ر�
    closesocket(remoteSocket);
    closesocket(listenSocket);
    return;
}
