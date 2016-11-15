#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "klient.h"

struct klient *klient_vytvor_klienta(int fd, char * jmeno_hrace){
    klient* kli = (klient*) malloc(sizeof(klient));
    kli->doba_necinosti=0;
  
    kli->fd = fd;
    kli->herni_mistnost=-1;
    kli->jmeno_hrace = malloc(sizeof(10));
    kli->jmeno_hrace = jmeno_hrace;
    kli->skore = 0;
    kli->kolo = 0;
    kli->pripojen = 1;
    printf("vytvarim hrace se jmenem %s na pozici %d \n", jmeno_hrace, fd);
    return kli;
}
int metoda(){
    return 1;
}
int klient_vynuluj_dobu_necinosti(struct klient hrac){
    hrac.doba_necinosti = 0;
}
int klient_inkrementuj_dobu_necinosti(struct klient hrac){
    hrac.doba_necinosti++;
}
int klient_prirad_herni_mistnost(struct klient hrac, int mistnost){
    hrac.herni_mistnost = mistnost;
}
int klient_odeber_herni_misnost(struct klient hrac){
    hrac.herni_mistnost = -1;
}
int klient_odpoj(struct klient hrac){
    hrac.pripojen = 0;
}


int klient_pripoj(struct klient hrac){
    hrac.doba_necinosti = 0;
    hrac.pripojen = 1;
    
}