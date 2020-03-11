#include "SocketV.h"

int main(){
	SocketV_init();
	struct SOCKETV socket = SocketV(SOCKETV_PRVE, "127.0.0.1", 4000);
	SocketV_listen(socket, 20);
	struct SOCKETV conn = SocketV_accept(socket);
	
	char *str = "Hello World!";
	SocketV_send(conn, str);
	
	SocketV_Close(conn);
	SocketV_Close(socket);

	SocketV_clean();

	return 0;
}
