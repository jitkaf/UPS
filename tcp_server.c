
#include <stdio.h>
#include <string.h>
#include "tcp_server.h"


int tcp_server_send_message(int fd, char * poslat, int length){
    int a2write = strlen(poslat);

   /* char *msg;
    memset(&msg, 0,a2write + 2);*/
    char *msg=(char*)malloc(a2write +1);
    memcpy(msg, poslat, a2write);
   printf("Odesilam zpravu: %s na fd %d \n" , msg, fd );
  
   printf("delka %d", a2write);
  //msg[a2write] ='\n';
   msg[a2write] ='\0';
  // write(fd, "asponneco\0", 10);
  
    write(fd, msg, strlen(msg));
   
}

