#ifndef _SOCKET_TCP_CLIENT_H
#define _SOCKET_TCP_CLIENT_H

#include <netinet/in.h>
#include <qstring.h>

#include "mPacket.h"
#include "SocketClient.h"
#include "Socket.h"

class SocketTcpClient: public SocketClient
{
	public:
		SocketTcpClient(); 
	private:
}; 

#endif
