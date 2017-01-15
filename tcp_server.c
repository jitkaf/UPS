
#include "tcp_server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int tcp_server_send_message(int fd, char * poslat){
    int a2write = strlen(poslat);
    char *msg=(char*)malloc(a2write +2);
    memcpy(msg, poslat, a2write);
    printf(" \n hhh  Odesilam zpravu: %s na fd %d \n" , msg, fd );
    msg[a2write] ='\n';
    msg[a2write +1] ='\0';
    write(fd, msg, strlen(msg));
   
}

