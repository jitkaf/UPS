
#include "klienti.h"
#include "zpracovavac_zprav.h"

#include "tcp_server.h"
#include "klient.h"
#include <stdio.h>
#include <string.h>
//identifikator_sluzby|sve_id|sve_jmeno|zprava    : c|cc|zzzzzzzzzz|zzzzzzzzz......
int zpracovavac_zprav_vyhodnot_zpravu(int fd, char * msg, int pocet, struct klient* klienti){
   int pom;
    switch (msg[0]){
        case '1':  //pripojovani ztraceneho klienta
            if(msg[1]=='|'){
                pocet = zpracovavac_zprav_pokus_opetovne_pripojeni(fd, msg,pocet, klienti);
            }
            break;
        case '2': 
            if(msg[1]=='|'){
                zpracovavac_zprav_posli_zpet(fd, msg, klienti) ;
            }
            break;
        case '3': //broadcast
            if (msg[1]=='|'){
                zpracovavac_zprav_posli_vsem(fd, msg, klienti, pocet);
            }
            break;
        case '4': 
            //symuluj zahozeni zpravy
            break;
     }
        
    
    return pocet;
}

//identifikator_sluzby|sve_id|sve_jmeno|zprava    : c|cc|zzzzzzzzzz|zzzzzzzzz......
int zpracovavac_zprav_pokus_opetovne_pripojeni(int fd, char *msg, int pocet, struct klient* klienti){
    char* cislo = msg[2] + msg[3];
    int id = atoi(cislo);
    int pom;
    char * jmeno_hrace = msg[5] + msg[6] + msg[7] + msg[8] + msg[9] + msg[10] + msg[11] + msg[12] + msg[13] + msg[14];
    pom = klienti_zkus_znovu_propojeni(fd, id, klienti, jmeno_hrace, pocet);
    if (pom == 0){
        tcp_server_send_message(fd, "Klient znovu pripojen, id = " + id, 0);
       
    }
    else{
        pom = klienti_pridej_klienta(fd, jmeno_hrace, klienti, pocet);
        if (pom == -1){
            tcp_server_send_message(fd, "nezdarilo se ", 1);
        }
        else{
            pom++;
            tcp_server_send_message(fd, "Klient vytvoren ", 1);
        }
             
    }
}

                                                   
int zpracovavac_zprav_posli_zpet(int fd, char *msg, struct klient * klienti){
    int delka = strlen(msg);
    int vel = delka-15;
    char * zprava =malloc(vel);
    memcpy(zprava, msg +15, delka-16);
    tcp_server_send_message(fd, zprava, 1);
    free(zprava);
    return 0;
}

int zpracovavac_zprav_posli_vsem(int fd, char *msg, struct klient *klienti, int pocet){
    int delka = strlen(msg);
    int i  ;
    int vel = delka-15;
    char * zprava2 =malloc(vel);
    memcpy(zprava2, msg +15, delka-16);
    for (i=0; i<pocet; pocet++){
        if(klienti[i].pripojen == 1){
             tcp_server_send_message((klienti + i)->fd, zprava2, 1);
        }
    }
    free(zprava2);
    return 0;
}