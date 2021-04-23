// socketͨ��  ������
//TCP���ڿͻ��˺ͷ�����֮���ṩ�ɿ����ֽ������䣨���ܵ�����
//#include "stdafx.h" //stdafx.h��û�к����⣬ֻ�Ƕ���һЩ����������ʹ��������ĳ�������32λ�Ĳ���ϵͳ�����¹���
#pragma comment(lib, "ws2_32.lib")//����Winsock2.h�ľ�̬���ļ�
#include <Winsock2.h>//winsock��2���ͷ�ļ��������ж��ֺ������԰���ʹ��Winsock
#include <WS2tcpip.h>//���û��ȡ�׽���ѡ��
#include <stdio.h>//��׼�������ͷ�ļ�
#include <string.h>//����һЩ���õ�C�ַ���������
#include <stdlib.h>//������C���Ե�һЩ���ÿ⺯��
#include <thread>//����std::thread�߳���
#include <iostream>//��ʾ���������
void func(SOCKET arg, SOCKADDR_IN client_addr, int pos)// socket���, SOCKADDR_IN �������׽�������
{
    char recvBuf[128];//���յ��ַ��� ����Buf,�����ó���Ϊ128
    char sendBuf[128];//���͵��ַ��� ����Buf�����ó���Ϊ128
    char tempBuf[256];//��ʱ�ַ��������ó���Ϊ256
    int sockConn = arg;
    while (true)
    {
        //�ӿͻ��˽�����Ϣ
        printf("wait receive client message :\n");//������ȴ����տͻ��˵���Ϣ��
        recv(sockConn, recvBuf, 128, 0);//
        // ��һ�������������������׽���
        // �ڶ������������յ��ַ���
        // ���������������յ��ַ�������
        // ���ĸ���������Ժ�����Ϊ����Ӱ�죬һ������Ϊ0
        //�����ͻ��˵�ַ��Ϣ
        char ipClient[16];//�ͻ�IP�ַ��������ó���Ϊ16
        inet_ntop(AF_INET, &client_addr.sin_addr, ipClient, sizeof(ipClient));//��һ������ָ����ַ�壬����TCP/IPЭ����׽��֣���ַ��ΪAF_INET���ڶ�������ָ���׽��ֵ�IP��ַ��sin_addr�����������������û�IP�����ĸ��������û�IP��ַ�Ĵ�С��
        printf("%s said: %s\n", ipClient, recvBuf);//������û�IP said: �����ַ�����
        //��ͻ��˷�����Ϣ
        gets_s(sendBuf);
        send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);// 
        // ��һ�������������������׽���
        // �ڶ���������Ҫ���͵��ַ���
        // �����������������ַ�������
        // ���ĸ���������Ժ�����Ϊ����Ӱ�죬һ������Ϊ0
    }
}
int main()
{
    std::cout << "Hello World!\n";//ʹ��std::���ڵ��ñ�׼�����ռ䣬�����Hello World!��
/*
WSAStartup������Ӧ�ó����DLL���õĵ�һ��Windows Sockets������
������Ӧ�ó����DLLָ��Windows Sockets API�İ汾�ż�����ض�Windows Socketsʵ�ֵ�ϸ�ڡ�
Ӧ�ó����DLLֻ����һ�γɹ���WSAStartup()����֮����ܵ��ý�һ����Windows Sockets API������
*/
    WORD wVersionRequested;// wVersionRequested��Windows Sockets API�ṩ�ĵ��÷���ʹ�õ���߰汾��
    WSADATA wsaData;// ����ṹ�����wsaData, �����洢��WSAStartup�������ú󷵻ص�Windows Sockets����
    int err;//�������ͱ���err
    wVersionRequested = MAKEWORD(1, 1);//��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ�ֽ�
    err = WSAStartup(wVersionRequested, &wsaData);//��winsock���г�ʼ��������һ��Winsock��汾
    if (err != 0) { return 0; }
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE����ȡ��16���������λ��HIBYTE����ȡ��16����������Ǹ��ֽڵ�����
    {
        WSACleanup();//��һ�����̵߳Ļ����£�WSACleanup������ֹ��Windows Sockets�������߳��ϵĲ�����
        return 0;
    }//���а汾���
    // ����洢�̵߳�����
    std::thread threads[10];//ʹ��std��thread����һ���̶߳���
    int thread_num = 0;//�ȼ��̸߳���Ϊ0
    /*socketͨѶ*/
    //�����׽���
    SOCKET Svr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//����SOCKET����Svr,AF_INETָIPV4�汾, ��һ��������ʾipЭ���壬�ڶ���������ʾ��������ʽ��������������TCPЭ�顣
    SOCKADDR_IN addr;//�����ű��ص�ַ��Ϣ�Ľṹ�����addr
    //Ҫ�󶨵Ļ�����Ϣ
    addr.sin_family = AF_INET;//sin_familyָЭ���壬һ����AF_INET,��ʾ����ipv4Э��
    addr.sin_port = htons(6002);//���˿ںţ�6002������sin_port, htons ����������ת���������ֽ���
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//htonl��������ת���������ֽ���
    //���а�
    int len = sizeof(sockaddr);
    bind(Svr, (struct sockaddr*) & addr, len);//ָ�����֡����͡�����
    //�����׽���
    int ret = listen(Svr, 10); //��һ��������Ҫ������socket���׽��֣�,�ڶ����������ȴ����Ӷ��е���󳤶�
    if (ret == SOCKET_ERROR)//����������
    {
        printf("����ʧ��\n");
        closesocket(Svr);//�ͷ��׽���Svr
    }
    //�洢�������ӵ��׽�����Ϣ
    SOCKADDR_IN addrClient;
    while (true)
    {
        //�������ӣ�����һ��socket
        SOCKET sockConn = accept(Svr, (struct sockaddr*) & addrClient, &len);
        if (sockConn == INVALID_SOCKET)
        {
            //printf("��Чsocket\n");
            continue;
        }
        //��ͨѶϸ�ڷ����߳��ﴦ��
        threads[thread_num] = std::thread(func, sockConn, addrClient, thread_num);
        thread_num++;
        if (thread_num == 5)
        {
            printf("�̳߳شﵽ��������");
        }
    }
    //�ȴ��߳̽���
    for (int i = 0; i < thread_num; i++)
        threads[i].join();
    //�ͷ��׽���
    closesocket(Svr);
    WSACleanup();//��ֹ���׽��ֿ��ʹ��
    return 0;
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
