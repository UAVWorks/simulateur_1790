#include "XPlaneUDPWorker.h"

static void XPlaneUDPWorker::XPlaneUDPWorker(void)
{

}

static void XPlaneUDPWorker::app(void)
{
    SOCKET sock = init_connection();
    char buffer[BUF_SIZE];
    /* the index for the array */
    int actual = 0;
    int max = sock;
    /* an array for all clients */
    Client clients[1];

    fd_set rdfs;

    while(1)
    {
        FD_ZERO(&rdfs);

        /* add STDIN_FILENO */
        FD_SET(STDIN_FILENO, &rdfs);

        /* add the connection socket */
        FD_SET(sock, &rdfs);

        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
           perror("select()");
           exit(errno);
        }

        /* something from standard input : i.e keyboard */
        if(FD_ISSET(STDIN_FILENO, &rdfs))
        {
           /* stop process when type on keyboard */
           break;
        }
        else if(FD_ISSET(sock, &rdfs))
        {
           /* new client */
           SOCKADDR_IN csin = { 0 };

           /* a client is talking */
           read_client(sock, &csin, buffer);

           if(check_if_client_exists(clients, &csin, actual) == 0)
           {
               if(actual != MAX_CLIENTS)
                   {
                       Client c = { csin };
                       strncpy(c.name, buffer, BUF_SIZE - 1);
                       clients[actual] = c;
                       actual++;
                   }
                }
            else
            {
               Client *client = get_client(clients, &csin, actual);
               if(client == NULL) continue;
               send_message_to_all_clients(sock, clients, client, actual, buffer, 0);
            }
        }
    }

    end_connection(sock);
}


static int XPlaneUDPWorker::init_connection(void)
{
    /* UDP so SOCK_DGRAM */
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    SOCKADDR_IN sin = { 0 };

    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
    {
        perror("bind()");
        exit(errno);
    }

    return sock;
}


static void XPlaneUDPWorker::end_connection(int sock)
{
    closesocket(sock);
}


static int XPlaneUDPWorker::read_client(SOCKET sock, SOCKADDR_IN *sin, char *buffer)
{
    int n = 0;
    size_t sinsize = sizeof *sin;

    if((n = recvfrom(sock, buffer, BUF_SIZE - 1, 0, (SOCKADDR *) sin, &sinsize)) < 0)
    {
        perror("recvfrom()");
        exit(errno);
    }

    buffer[n] = 0;

    return n;
}

static void XPlaneUDPWorker::write_client(SOCKET sock, SOCKADDR_IN *sin, const char *buffer)
{
    if(sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR *) sin, sizeof *sin) < 0)
    {
        perror("send()");
        exit(errno);
    }
}