
#include "zpracovavac_zprav.h"

#include "tcp_server.h"
#include "klient.h"
#include "globalni_promenne.h"
#include <stdio.h>
#include <string.h>
//identifikator_sluzby|sve_id|sve_jmeno|zprava    : c|cc|zzzzzzzzzz|zzzzzzzzz......
int zpracovavac_zprav_vyhodnot_zpravu(int fd, char * msg, struct klient* klienti){
   int pom;
    switch (msg[0]){
        case '1':  //pripojovani ztraceneho klienta
            if(msg[1]=='|'){
                printf("jdu na to");
                zpracovavac_zprav_pokus_opetovne_pripojeni(fd, msg, klienti);
            }
            break;
        case '2': 
            if(msg[1]=='|'){
                zpracovavac_zprav_posli_zpet(fd, msg, klienti) ;
            }
            break;
        case '3': //broadcast
            if (msg[1]=='|'){
                zpracovavac_zprav_posli_vsem(fd, msg, klienti);
            }
            break;
        case '4': //odpojit klienta
            if (msg[1]=='|'){
                
            }
            break;
     }
        
    
    return 0;
}

//identifikator_sluzby|sve_id|sve_jmeno|zprava    : c|cc|zzzzzzzzzz|zzzzzzzzz......
    zpracovavac_zprav_pokus_opetovne_pripojeni(int fd, char *msg, struct klient* klienti){
    printf("zacatek metody");
    char *cislo =malloc(2);
    memcpy(cislo, msg+2, 2);

    printf("cislo je: %s", cislo);
    int id = atoi(cislo);
    int pom;
    char *jmeno_hrace = malloc(10);
    memcpy(jmeno_hrace, msg+5, 10);
   
    pom = klienti_zkus_znovu_propojeni(fd, id, klienti, jmeno_hrace);
    if (pom == 0){
        tcp_server_send_message(fd, "Klient znovu pripojen, id = " + id, 0);
       
    }
    else{
        klienti_pridej_klienta(fd, jmeno_hrace, klienti);
        if (pom == -1){
            char *zprava = malloc(20);
            zprava="nezdarilo se ";
            tcp_server_send_message(fd, zprava, 1);
        }
        else{
            pom++;
            char zprava[20];
            memcpy(zprava, "efwfw", 5);
         //   zprava="Klient vytvoren.";
            zprava[5]='\0';
            
            tcp_server_send_message(fd, zprava, 1);
        }
             
    }
   
}

                                                   
int zpracovavac_zprav_posli_zpet(int fd, char *msg, struct klient * klienti){
    int delka = strlen(msg);
    printf("v metode prijata yprava je %s \n", msg);
    int vel = delka-15;
    char * zprava =(char*)malloc(vel);
    memcpy(zprava, msg +15, delka-15);
    tcp_server_send_message(fd, zprava, 1);
   // free(zprava);
    return 0;
}

int zpracovavac_zprav_posli_vsem(int fd, char *msg, struct klient *klienti){
    int delka = strlen(msg);
    int i  ;
    int vel = delka-15;
    char * zprava2 =(char*) malloc(vel);
    memcpy(zprava2, msg +15, delka-15);
    //printf("-----------cislo------- %d \n", pocet);
    for (i=0; i<GLOBAL_pocet; i++){
        printf("posilam a i je %d", i);
        if((klienti + i)->pripojen == 1){
             tcp_server_send_message((klienti + i)->fd, zprava2, 1);
        }
    }
   // free(zprava2);
    return 0;
}