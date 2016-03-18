#ifndef XPLANEUDPWORKER_H
#define XPLANEUDPWORKER_H

#include "Dataref.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h> /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)

#define CRLF		"\r\n"
#define PORT	 	49000
#define MAX_CLIENTS 	1

#define BUF_SIZE	1024


class XPlaneUDPWorker
{
private:
	
	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
	typedef struct in_addr IN_ADDR;

public:

	static void XPlaneUDPWorker(void);
	static void end(void);
	static void app(void);
	static int init_connection(void);
	static void end_connection(int sock);
	static int read_client(SOCKET sock, SOCKADDR_IN *csin, char *buffer);
	static void write_client(SOCKET sock, SOCKADDR_IN *csin, const char *buffer);
	// static void send_message_to_all_clients(int sock, Client *clients, Client *client, int actual, const char *buffer, char from_server);
	// static void remove_client(Client *clients, int to_remove, int *actual);
	// static int check_if_client_exists(Client *clients, SOCKADDR_IN *csin, int actual);
	// static Client* get_client(Client *clients, SOCKADDR_IN *csin, int actual);
};

#endif /* guard */