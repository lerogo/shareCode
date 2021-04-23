//socketͨ��  �ͻ���
//TCP���ڿͻ��˺ͷ�����֮���ṩ�ɿ����ֽ������䣨���ܵ�����
//#include "stdafx.h"//stdafx.h��û�к����⣬ֻ�Ƕ���һЩ����������ʹ��������ĳ�������32λ�Ĳ���ϵͳ�����¹���
#pragma comment(lib, "ws2_32.lib")//����Winsock2.h�ľ�̬���ļ�
#include <Winsock2.h>//winsock��2���ͷ�ļ��������ж��ֺ������԰���ʹ��Winsock
#include <WS2tcpip.h>//���û��ȡ�׽���ѡ��
#include <stdio.h>//��׼�������ͷ�ļ�
#include <string.h>//����һЩ���õ�C�ַ���������
#include <stdlib.h>//������C���Ե�һЩ���ÿ⺯��
#include <thread>//����std::thread�߳���
#include <iostream>//��ʾ���������
void new_client(int pos)
{
    WORD wVersionRequested;//wVersionRequested��Windows Sockets API�ṩ�ĵ��÷���ʹ�õ���߰汾��
    WSADATA wsaData;//����ṹ�����wsaData
    int err;//�������ͱ���err
    wVersionRequested = MAKEWORD(1, 1);//��һ������Ϊ��λ�ֽڣ��ڶ�������Ϊ��λ�ֽ�
    err = WSAStartup(wVersionRequested, &wsaData);//��winsock���г�ʼ��������һ��Winsock��汾
    if (err != 0) { return; }
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)//LOBYTE����ȡ��16���������λ��HIBYTE����ȡ��16����������Ǹ��ֽڵ�����
    {
        WSACleanup();//��һ�����̵߳Ļ����£�WSACleanup������ֹ��Windows Sockets�������߳��ϵĲ�����
        return;
    }
    SOCKET Client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//��һ��������ʾipЭ���壬�ڶ���������ʾ��������ʽ��������������TCPЭ��
    SOCKADDR_IN Server;//�����ű��ص�ַ��Ϣ�Ľṹ�����Server
    // Ҫ���ӵĻ�����Ϣ
    Server.sin_family = AF_INET;//sin_familyָЭ���壬һ����AF_INET,��ʾ����ipv4Э��
    Server.sin_port = htons(6002);//���˿ںţ�6002������sin_port, htons ����������ת���������ֽ���
    inet_pton(AF_INET, "127.0.0.1", &Server.sin_addr); //���ʮ���Ƶ�ַת���������ֽ���
    // �����˷�������
    int ret = connect(Client, (struct sockaddr*) & Server, sizeof(Server));//
        //��һ���������������׽���
        //�ڶ���������Ҫ���ӵ��׽��ֵ�ַ
        //��������������λ����
    if (ret == SOCKET_ERROR)
    {
        printf("����ʧ��\n");
        closesocket(Client);//�ͷ��׽���Client
        WSACleanup();//��ֹ���׽��ֿ��ʹ��
        return;
    }
    char recvBuf[128];//�����ַ��������ó���Ϊ128
    char sendBuf[128];//�����ַ��������ó���Ϊ128
    while (true)
    {
        printf("please input message:\n");//�������������Ϣ����
        gets_s(sendBuf);//�õ�����ַ���
        sprintf_s(sendBuf, "%s_%d", sendBuf, pos);
        send(Client, sendBuf, strlen(sendBuf) + 1, 0);//
        // ��һ�������������������׽���
        // �ڶ���������Ҫ���͵��ַ���
        // �����������������ַ�������
        // ���ĸ���������Ժ�����Ϊ����Ӱ�죬һ������Ϊ0
        recv(Client, recvBuf, 128, 0);//
        // ��һ�������������������׽���
        // �ڶ���������������Ϣ���ַ���
        // ��������������������ַ�������󳤶�
        // ���ĸ���������Ժ�����Ϊ����Ӱ�죬һ������Ϊ0
        char ipServer[16];//����������IP�����ô�СΪ16�ֽ�
        inet_ntop(AF_INET, &Server.sin_addr, ipServer, sizeof(ipServer));//��һ������ָ����ַ��ΪAF_INET���ڶ�������ָ���׽��ֵ�IP��ַ��sin_addr���������������Ƿ�����IP�����ĸ������Ƿ�����IP��ַ�Ĵ�С
        printf("%s said: %s\n", ipServer, recvBuf);//�����������IP said: �����ַ�����
    }
    closesocket(Client);//�ͷ��׽���
    WSACleanup();//��ֹ���׽��ֿ��ʹ��
}
int main()
{
    std::cout << "Hello World!\n";//�����Hello World!��
    std::thread threads[10];//�����̶߳���
    int client_num = 5;
    for (int i = 0; i < client_num; i++)
        threads[i] = std::thread(new_client, i);
    for (int i = 0; i < client_num; i++)//�ȴ��߳̽���
        threads[i].join();
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
