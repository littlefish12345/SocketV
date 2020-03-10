#include <winsock2.h>
#include "SocketV.h"

int main(){
	SocketV_init();
	SOCKETV socket = SocketV(SOCKETV_PRVE, "127.0.0.1", 123);
	SOCKETV_listen(socket, 20);
	conn = SocketV_accept(socket);
	
	char *str = "Hello World!";
	SocketCONN_send(conn, str);
	
	SocketV_Close(conn);
	SocketV_Close(socket);

	WSACleanup();

	return 0;
}
