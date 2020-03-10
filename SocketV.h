#define SOCKETV_PRVE 4
#define SOCKETV_PRVE6 6

#if ((defined _WIN32) || (defined _WIN32))

#include <winsock2.h>
#include <stdio.h>
#pragma comment (lib, "ws2_32.lib")? //加载 ws2_32.dll

//初始化 DLL
WSADATA wsaData;
WSAStartup(MAKEWORD(2, 2), &wsaData);

#define SOCKETV_INET AF_INET
typedef struct SOCKETV{
	Socket socket;
	int protocol_version;
};

SOCKETV SocketV (int protocol_version, char *ip, int port) {
	//创建socket
	if (protocol_version == SOCKETV_PRVE){
		SOCKET socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //使用IPv4
	} else if (protocol_version == SOCKETV_PRVE6){
		SOCKET socket = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP); //使用IPv6
	} else {
		throw protocol_version;
	}
	
	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	
	if (protocol_version = SOCKETV_PRVE){
		sockAddr.sin_family = PF_INET; //使用IPv4
	} else if (protocol_version = SOCKETV_PRVE6){
		sockAddr.sin_family = PF_INET6; //使用IPv6
	} else {
		throw protocol_version;
	}
	
	sockAddr.sin_addr.s_addr = inet_addr(ip); //IP
	sockAddr.sin_port = htons(port); //端口
	bind(socket.socket, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	
	SOCKETV SocketV = {socket, protocol_version, listen:SocketV_listen, accept:SocketV_accept};
	return SocketV;
}

void SocketV_listen (SOCKETV socket, int listen_num) { //进入监听状态
	listen(socket, listen_num);
}

SOCKETV SocketV_accept(SOCKETV socket) { //接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET client = accept(socket, (SOCKADDR*)&clntAddr, &nSize);
	SOCKETV SocketCONN = {client, socket.protocol_version}
	
	return SocketCONN;
}

void SocketCONN_send(SOCKETV client, char *str) { //向客户端发送数据
	send(client.socket, str, strlen(str)+sizeof(char), NULL);
}

void SocketV_Close(SOCKETV socket) { //关闭套接字
	closesocket(socket);
}

#endif
