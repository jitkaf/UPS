#ifndef TCP_SERVER_H
#define TCP_SERVER_H

struct tcp_server
{
    int socket;

};

int tcp_server_send_message(int fd, char * msg, int length);





#endif // TCP_SERVER_H