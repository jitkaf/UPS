#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "klient.h"
#include "klienti.h"


int funkce (){
    return 0;
}
int klienti_vrat_fd_klienta(struct klient* klienti, char* jmeno_hrace, int pocet){
    int fd;
    int navrat=klienti_vrat_id_klienta(klienti, jmeno_hrace, pocet);
    if (navrat == -1) {
        return navrat;
    }
    fd = (klienti + navrat)->fd;
    printf("FD JE %d\n" , fd);
   
    return fd;
    return 5;
}

int klienti_vrat_id_klienta(struct klient* klienti, char* jmeno_hrace, int pocet){
   int i;
    for(i=0; i<pocet; i++){
        if (strcmp((klienti+i)->jmeno_hrace, jmeno_hrace) == 0){
            printf("POROVNAVANI %d \n",  i);
            return i;
        }
    }
   i=-1;
    return i;
    
}

struct klient* klienti_pridej_klienta(int fd, char* jmeno_hrace, struct klient* klienti, int pocet ){
  //  (klienti+pocet)  = klient_vytvor_klienta(fd, jmeno_hrace);
    memcpy(klienti + pocet, klient_vytvor_klienta(fd, jmeno_hrace), sizeof(struct klient));
    return klienti;
   
}

struct klient* klienti_odeber_klienta(int id, struct klient* klienti, int pocet){
    int i;
    for(i=id; i <pocet-1; i++){
        memcpy(klienti + i, klienti + i +1, sizeof(struct klient));
    }
    return klienti;
}

int klienti_zkus_znovu_propojeni(int fd, int id, struct klient * klienti, char *jmeno_hrace, int pocet){
   
    if ((id<pocet)&&(klienti[id].pripojen == 0) && (strcmp(klienti[id].jmeno_hrace, jmeno_hrace) == 0)){
        //pripojuji ztraceneho hrace
        (klienti +id)->doba_necinosti = 0;
        (klienti + id)->pripojen = 1;
        (klienti +id)->fd = fd;
        //zde by mozna bylo jeste enco o hre rozehrane
        return 0;
    } 
   //klienti_pridej_klienta(fd, jmeno_hrace, klienti, pocet); - spis venku metody
    return -1;
}