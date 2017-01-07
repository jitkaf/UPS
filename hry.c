/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hry.c
 * Author: jitka
 * 
 * Created on 18. prosince 2016, 18:35
 */
#include "hry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "konstanty.h"
#include "globalni_promenne.h"
#include "tcp_server.h"
#include "hra.h"
#include "klient.h"
#include <pthread.h>
#include "herni_otazky.h"

int hry_prirad_do_hry(int id_hrac){
    int i;
    printf("jsem v metode hry_prirad_do_hry id hrace je %d \n", id_hrac);
    for (i=0; i<MAX_HER; i++){
        //v ifech nejaky zamek aby se to provedlo atomicky
        if ((GLOBAL_hry + i)->stav == 0){
            (GLOBAL_hry + i)->stav =1;
            (GLOBAL_hry + i)->id_hrac_jedna = id_hrac;
           // (GLOBAL_hry +i)->vlakno = -1;
            printf("prida prvni hrac \n");
            return 0;
        }
        else if ((GLOBAL_hry + i)->stav == 1){ ///pridavam druheho hrace
            (GLOBAL_hry + i)->stav =2;
            (GLOBAL_hry + i)->id_hrac_dva = id_hrac;
            //ZDE BUDU JESTE TVORIT VLAKNO PRO HRU A HRA ZACNE
            printf("pridan druhy hrac \n");
            hry_vytvor_vlakno_hry(i);
            
            return 0;
        }
    }
    
    return -1; //signalizuje ze je plno
}

int hry_vytvor_vlakno_hry(int id_hry){
    printf("jsem ve hry_vytvor_vlakno_hry\n");
        int *arg = malloc(sizeof(*arg));
        *arg = id_hry;
        
        
         if ((GLOBAL_hry +id_hry)->prirazene_vlakno != 0){
           pthread_join((GLOBAL_hry +id_hry)->vlakno, NULL); 
        }    
        (GLOBAL_hry +id_hry)->prirazene_vlakno=1;
        pthread_create( &((GLOBAL_hry +id_hry)->vlakno), 0, hry_smycka_vlakna, arg);
        
       
         //temer urcite musi bejt jinde jinak nebude paraelni, zasekne se tu
            //to bude nekde kde se rusi hra
    return 0;
}

void *hry_smycka_vlakna( void *arg){
   int id_hry =*((int *) arg);
   int i;
   int fd_prvni = (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->fd;
   int fd_druhej = (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->fd;
   (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu =3;
   (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->stav_stavoveho_diagramu=3;
   for(i=0; i <POCET_OTAZEK; i++){
       
       
      
       tcp_server_send_message(fd_prvni,(otazky +i)->text,29);
       tcp_server_send_message(fd_druhej,(otazky +i)->text,4);
       
       
       usleep(10000000);
       while(((GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->zamek_odpovedi !=0) || ((GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->zamek_odpovedi !=0)){
           usleep(10);
       }
       (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->zamek_odpovedi =1;
       (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->zamek_odpovedi =1;
       
       hra_vyhodnot_odpoved(GLOBAL_hry+id_hry, (otazky +i)->odpoved,(GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->odpoved, (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->odpoved );
      (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->odpoved =-1;
      (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->odpoved =-1;
      
      (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->zamek_odpovedi =0;
      (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->zamek_odpovedi =0;
       
   }
   
   while(((GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->zamek_odpovedi !=0) || ((GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->zamek_odpovedi !=0)){
       printf("zamek");   
       usleep(10);
   }
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->zamek_odpovedi =1;
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->zamek_odpovedi =1;
    if((GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->skore > (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->skore){
        tcp_server_send_message(fd_prvni,"5|1",3);
        tcp_server_send_message(fd_druhej,"5|2",3);
    }
    if((GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->skore < (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->skore){
        tcp_server_send_message(fd_prvni,"5|2",3);
        tcp_server_send_message(fd_druhej,"5|1",3);
    }
    else{
         tcp_server_send_message(fd_prvni,"5|0",3);
         tcp_server_send_message(fd_druhej,"5|0",3);
    }
   
   
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->stav_stavoveho_diagramu=1;
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu=1;
    
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->zamek_odpovedi =0;
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->zamek_odpovedi =0;
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu =1;
   (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->stav_stavoveho_diagramu=1;
     printf("\n druhej: %d \n", (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->stav_stavoveho_diagramu);
    printf("\n jeden:  %d \n", (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu);
    hra_vyrezetuj_hru((GLOBAL_hry+id_hry));
  /* 
   (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->stav_stavoveho_diagramu=1;
    (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu=1;*/
  (GLOBAL_hry + id_hry)->stav =0;
   printf("borkyne ziskava i %d \n", id_hry);
     
}

