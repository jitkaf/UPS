
#include <stdio.h>
#include <string.h>
#include "tcp_server.h"


int tcp_server_send_message(int fd, char * msg, int length){
    int a2write;
   printf("Odesilam zpravu: %s \n" , msg );
   a2write = strlen(msg);
   msg[a2write] ='\n';
   msg[a2write + 1] ='\0';
    write(fd, msg, length);
}

