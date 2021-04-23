// Extremely simple, stream client example.�򵥵Ŀͻ���ʾ��
// Works in conjunction with Server.cpp.��Server.cppЭͬ����
// The program attempts to connect to the server and port specified on the command line. ���������ӵ���������ָ���ķ������Ͷ˿ڡ�
// The Server program prints the needed information when it is started. Once connected,the program sends data to the server, waits for a response and then exits. ����������������ʱ��ӡ�������Ϣ�����Ӻ󣬳�����������������ݣ��ȴ���Ӧ��Ȼ���˳���
// Compile and link with wsock32.lib. ���벢���ӵ�wsock32.lib #pragma comment(lib,�� wsock32.lib��)
// Pass the server name and port number on the command line. ���������ϴ��ݷ��������ƺͶ˿ںš�
// Example: Client MyMachineName 2000���Ӷ˿�2000���ҵ�����������sc-PC
#pragma comment(lib,"wsock32.lib")
#include <stdio.h>   //��׼�������ͷ�ļ�
#include <winsock.h> //�����Winsock2.h���ϰ汾
#include <string.h>  //string��
// Function prototype����Э�麯��
void StreamClient(char* szServer, short nPort);
// Helper macro for displaying errors��������ʾ����
//ʹ�� WSAGetLastError() ���� �������һ�εĴ������,Ϊ���ṩ�ͽ����Ķ��̻߳�������ݡ�
#define PRINTERROR(s) fprintf(stderr, "\n%: %d\n", s, WSAGetLastError())        //����printerror()����:ϵͳ������ʾ��Ϣ�����������Ϣ��ת��ʾ

void main(int argc, char** argv)
{
    WORD wVersionRequested = MAKEWORD(1, 1); //wVersionRequested��Windows Sockets API�ṩ�ĵ��÷���ʹ�õ���߰汾�ţ�MAKEWORD(1, 1)��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ�ֽ�
    WSADATA wsaData;                         //����ṹ�����wsaData
    int nRet;
    short nPort;
    //��������Ͷ˿ڲ���
    if (argc != 3)
    {
        fprintf(stderr, "\nSyntax: client ServerName PortNumber\n"); //fprintf()��������ָ����format(��ʽ)������Ϣ(����)����stream(��)ָ�����ļ�
        return;
    }
    nPort = atoi(argv[2]);
    //��WinSock���г�ʼ�������汾
    nRet = WSAStartup(wVersionRequested, &wsaData); //WSAStartup()���������ϵͳ˵��Ҫ���ĸ����ļ�,��˾Ϳ��Խ����ļ��뵱ǰ��Ӧ�ó���󶨣��Ӷ����øð汾��socket�ĸ��ֺ���,WSAStartup()������Ӧ��socket��󶨡�
    if (wsaData.wVersion != wVersionRequested)      //wVersionRequested Ҫʹ�õ� Windows Sockets API �汾
    {
        fprintf(stderr, "\n Wrong version\n"); // fprintf()��������ָ����format(��ʽ)������Ϣ(����)����stream(��)ָ�����ļ�
        return;
    }
    StreamClient(argv[1], nPort);
    //�ͷ�WinSock
    WSACleanup();
}
void StreamClient(char* szServer, short nPort) //�����ͻ���
{
    printf("\nStream Client connecting to server: %s on port: %d",
        szServer, nPort);
    //�ҷ�����
    LPHOSTENT lpHostEntry;
    lpHostEntry = gethostbyname(szServer); // gethostbyname()����������������������ȡ��ַ������ϵͳ�ṩ�Ŀ⺯��
    if (lpHostEntry == NULL)
    {
        PRINTERROR("gethostbyname()"); //printerror()���ܣ�ϵͳ������ʾ��Ϣ�������Ƿ�����ʾ��gethostbyname()
        return;
    }
    //����TCP/IP���׽���
    SOCKET theSocket;
    theSocket = socket(AF_INET,      // ��ַ��
        SOCK_STREAM,  //sock_stream��Ӧ��TCPЭ�飬SOCK_DGRAM��ӦUDPЭ�飬SOCK_RAW��ӦԭʼSocket
        IPPROTO_TCP); //����protocol����ָ��socket��ʹ�õĴ���Э����
    if (theSocket == INVALID_SOCKET)
    {
        PRINTERROR("socket()"); //������ʾ��socket()
        return;
    }
    SOCKADDR_IN saServer;
    saServer.sin_family = AF_INET; // ѡ�� AF_INET ��Ŀ�ľ���ʹ�� IPv4 ����ͨ�š�IPv4 ʹ�� 32 λ��ַ����� IPv6 �� 128 λ��˵��������죬�������ھ�����ͨ�š�
    saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
    // ^�������ĵ�ַ
    saServer.sin_port = htons(nPort); //�������еĶ˿ں�
    //���ӷ�����
    int nRet;
    nRet = connect(theSocket,                //��һ���������������׽���
        (LPSOCKADDR)&saServer,    // Server address�ڶ���������Ҫ���ӵķ�������ַ
        sizeof(struct sockaddr)); //��������������������ַ�ĳ���
    if (nRet == SOCKET_ERROR)
    {
        PRINTERROR("socket()"); //������ʾ��socket()
        closesocket(theSocket); //�ͷ��׽���
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

        nRet = send(theSocket,     //���ӵ��׽���
            szBuf,         //���ݻ�����
            strlen(szBuf), //���ݳ���
            0);            // Flags
        if (nRet == SOCKET_ERROR)
        {
            PRINTERROR("send()");   //������ʾ��send()
            closesocket(theSocket); //�ͷ��׽���
            return;
        }
        //�ȴ���Ӧ
        nRet = recv(theSocket,     //��һ�������������������׽���
            szBuf,         // Receive buffer�ڶ���������������Ϣ���ַ���
            sizeof(szBuf), // Size of receive buffer��������������������ַ�������󳤶�
            0);            // Flags���ĸ���������Ժ�����Ϊ����Ӱ�죬һ������Ϊ0
        if (nRet == SOCKET_ERROR)
        {
            PRINTERROR("recv()");   //������ʾ��recv()
            closesocket(theSocket); //�ͷ��׽���
            return;
        }

        //
        // ��ʾ���յ�������
        //
        printf("\nData received: %s", szBuf);
    }

    closesocket(theSocket); //�ͷ��׽���
    return;
}
