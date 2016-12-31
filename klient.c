#include "klient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 struct klient *klient_vytvor_klienta(int fd){
    klient* kli = (klient*) malloc(sizeof(klient));
    kli->doba_necinosti=0;
    kli->fd = fd;
    kli->herni_mistnost=-1;
    kli->jmeno_hrace = malloc(sizeof(10));
    kli->heslo = malloc(sizeof(10));
    kli->jmeno_hrace =NULL;
    kli->heslo = NULL;
    kli->skore = 0;
    kli->kolo = 0;
    kli->odpoved = 0;
    kli->stav_stavoveho_diagramu=0;
    kli->zamek_odpovedi =0;
    printf("vytvarim hrace s zatim neznamym jmenemna s fd %d \n", fd);
    return kli;
}



int metoda(){
    return 1;
}
int klient_vynuluj_dobu_necinosti(struct klient hrac){
    hrac.doba_necinosti = 0;
    return 0 ;
}
int klient_inkrementuj_dobu_necinosti(struct klient hrac){
    hrac.doba_necinosti++;
    return 0;
}
int klient_prirad_herni_mistnost(struct klient hrac, int mistnost){
    hrac.herni_mistnost = mistnost;
    return 0;
}
int klient_odeber_herni_misnost(struct klient hrac){
    hrac.herni_mistnost = -1;
    return 0;
}
int klient_odpoj(struct klient hrac){
    hrac.stav_stavoveho_diagramu = 5;
    return 0;
}



int klient_pripoj(struct klient hrac){
    hrac.doba_necinosti = 0;
    hrac.stav_stavoveho_diagramu = 1;
    
    return 0;
}

int klient_generuj_heslo(){
    //bude vylepseno :)
  
    return 5;
}

int klient_nastav_odpoved(struct klient hrac, int odpoved){
    if (hrac.zamek_odpovedi == 0) { // z vlakna nikdo necte, pokud ano, uz je pozde a odpoved se nezpracovava, jen si ulozim dobu necinosti hrace a nulu
        hrac.zamek_odpovedi = 1;
        if (hrac.odpoved = 0){
            hrac.doba_necinosti ++;
                    
        }
        else{
            hrac.odpoved = 0;
            hrac.doba_necinosti =0;
           
        }
        hrac.zamek_odpovedi = 0;
    }
    else{
        hrac.doba_necinosti = 0;
    }
    return 0;
}

int klient_dej_odpoved_hrace(struct klient hrac){
    int pom;
    if (hrac.zamek_odpovedi == 0){
        hrac.zamek_odpovedi =1;
        pom = hrac.odpoved;
        hrac.odpoved = 0;
        hrac.zamek_odpovedi = 0;
        return pom;
    }
    return -1; //signaulizuje ze nelze zrovna cist odpoved hrace
}