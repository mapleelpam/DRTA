

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#include <netdb.h>

#include "Error.h"
#include "SocketTcpClient.h"
#include "SocketClient.h"
#include "global.h"


SocketTcpClient::SocketTcpClient()
	: SocketClient(IPPROTO_TCP)
{
}

