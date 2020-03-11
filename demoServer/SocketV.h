#define SOCKETV_PRVE 4
#define SOCKETV_PRVE6 6

#if ((defined _WIN32) || (defined _WIN32))

#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")? //���� ws2_32.dll

//��ʼ�� DLL
WSADATA wsaData;

void SocketV_init () {
	WSAStartup(MAKEWORD(2, 2), &wsaData);
}

void SocketV_clean () {
	WSACleanup();
}

#define SOCKETV_INET AF_INET

struct SOCKETV{
	SOCKET socket;
	int protocol_version;
};

struct SOCKETV SocketV (int protocol_version, char *ip, int port) {
	//����socket
	SOCKET Socket;
	if (protocol_version == SOCKETV_PRVE){
		SOCKET Socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //ʹ��IPv4
	} else if (protocol_version == SOCKETV_PRVE6){
		SOCKET Socket = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP); //ʹ��IPv6
	}
	
	//���׽���
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	
	if (protocol_version = SOCKETV_PRVE){
		sockAddr.sin_family = PF_INET; //ʹ��IPv4
	} else if (protocol_version = SOCKETV_PRVE6){
		sockAddr.sin_family = PF_INET6; //ʹ��IPv6
	}
	
	sockAddr.sin_addr.s_addr = inet_addr(ip); //IP
	sockAddr.sin_port = htons(port); //�˿�
	bind(Socket, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	
	struct SOCKETV SocketV = {Socket, protocol_version};
	return SocketV;
}

void SocketV_listen (struct SOCKETV Socket, int listen_num) { //�������״̬
	listen(Socket.socket, listen_num);
}

struct SOCKETV SocketV_accept(struct SOCKETV Socket) { //���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET client = accept(Socket.socket, (SOCKADDR*)&clntAddr, &nSize);
	struct SOCKETV SocketCONN = {client, Socket.protocol_version};
	
	return SocketCONN;
}

void SocketV_send(struct SOCKETV client, char *str) { //��ͻ��˷�������
	send(client.socket, str, strlen(str)+sizeof(char), 0);
}

void SocketV_Close(struct SOCKETV Socket) { //�ر��׽���
	closesocket(Socket.socket);
}

#endif
