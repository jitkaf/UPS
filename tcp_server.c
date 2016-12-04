
#include <stdio.h>
#include <string.h>
#include "tcp_server.h"


int tcp_server_send_message(int fd, char * poslat, int length){
    int a2write = strlen(poslat);
    char *msg =malloc(a2write + 2);
    memcpy(msg, poslat, a2write);
   printf("Odesilam zpravu: %s na fd %d \n" , msg, fd );
  
   printf("delka %d", a2write);
  //msg[a2write] ='\n';
   msg[a2write-1] ='\0';
  // write(fd, "asponneco\0", 10);
   if (length==-1){
       msg="TIMEOUT\0";
        write(fd, msg, 8);
   }
   else{
        write(fd, msg, strlen(msg));
   }
}

