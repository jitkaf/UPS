#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "klient.h"
#include "klienti.h"
#include "globalni_promenne.h"

int funkce (){
    return 0;
}
int klienti_vrat_fd_klienta(char* jmeno_hrace){
    int fd;
    int navrat=klienti_vrat_id_klienta(jmeno_hrace);
    if (navrat == -1) {
        return navrat;
    }
    fd = (GLOBAL_klienti + navrat)->fd;
    printf("FD JE %d\n" , fd);
   
    return fd;
    return 5;
}

int klienti_vrat_id_klienta(char* jmeno_hrace){
   int i;
    for(i=0; i<GLOBAL_pocet; i++){
        if (strcmp((GLOBAL_klienti+i)->jmeno_hrace, jmeno_hrace) == 0){
            printf("POROVNAVANI %d \n",  i);
            return i;
        }
    }
   i=-1;
    return i;
    
}

int klienti_vrat_id_klienta_fd(int fd){
   int i;
    for(i=0; i<GLOBAL_pocet; i++){
        if ((GLOBAL_klienti+i)->fd == fd){
            printf("POROVNAVANI %d \n",  fd);
            return i;
        }
    }
   i=-1;
    return i;
    
}

int klienti_pridej_klienta(int fd, char* jmeno_hrace){
  //  (klienti+pocet)  = klient_vytvor_klienta(fd, jmeno_hrace);
    memcpy(GLOBAL_klienti + GLOBAL_pocet, klient_vytvor_klienta(fd, jmeno_hrace), sizeof(struct klient));
    return 0;
   
}

int klienti_odeber_klienta(int id){
    int i;
    for(i=id; i <GLOBAL_pocet-1; i++){
        //tady je asi chyba nebot zustane nekde ulozenej starej fd i po odpojeni*/
        memcpy(GLOBAL_klienti + i, GLOBAL_klienti + i +1, sizeof(struct klient));
        
    }
    GLOBAL_pocet--;
    return 0;
}

int klienti_zkus_znovu_propojeni(int fd, int id, char *jmeno_hrace){
    printf("zde \n");
    if ((id<GLOBAL_pocet)&&((GLOBAL_klienti+id)->pripojen == 0) && (strcmp((GLOBAL_klienti+id)->jmeno_hrace, jmeno_hrace) == 0)){
        //pripojuji ztraceneho hrace
        (GLOBAL_klienti +id)->doba_necinosti = 0;
        (GLOBAL_klienti + id)->pripojen = 1;
        (GLOBAL_klienti +id)->fd = fd;
        //zde by mozna bylo jeste enco o hre rozehrane
        return 0;
    } 
   //klienti_pridej_klienta(fd, jmeno_hrace, klienti, pocet); - spis venku metody
    return -1;
}