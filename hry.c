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

/**
 * Přiřadí hráče do hry, pohlídá si, který má bejt první a který druhý
 * @param id_hrac
 * @return 
 */
int hry_prirad_do_hry(int id_hrac) {
    int i;
    printf("Přiřazuji do hry hráče s indexem: %d \n", id_hrac);
    for (i = 0; i < MAX_HER; i++) {
        //v ifech nejaky zamek aby se to provedlo atomicky
        if ((GLOBAL_hry + i)->stav == 0) {
            (GLOBAL_hry + i)->stav = 1;
            (GLOBAL_hry + i)->id_hrac_jedna = id_hrac;
            printf("Do hry byl přidán první hráč. \n");
            (GLOBAL_klienti + id_hrac)->herni_mistnost = i;
            return 0;
        } else if ((GLOBAL_hry + i)->stav == 1) { ///pridavam druheho hrace
            (GLOBAL_hry + i)->stav = 2;
            (GLOBAL_hry + i)->id_hrac_dva = id_hrac;
            //ZDE BUDU JESTE TVORIT VLAKNO PRO HRU A HRA ZACNE
            printf("Do hry byl přidán druhý hrá \n");
            (GLOBAL_klienti + id_hrac)->herni_mistnost = i;
            hry_vytvor_vlakno_hry(i);

            return 0;
        }
    }

    return -1; //signalizuje ze je plno
}

/**
 * Vytvoří vlákno hry
 * @param id_hry
 * @return 
 */
int hry_vytvor_vlakno_hry(int id_hry) {
    printf("Vytvářím vlákno hry. \n");
    int *arg = malloc(sizeof (*arg));
    *arg = id_hry;

    if ((GLOBAL_hry + id_hry)->prirazene_vlakno != 0) {
        pthread_join((GLOBAL_hry + id_hry)->vlakno, NULL);
    }
    (GLOBAL_hry + id_hry)->prirazene_vlakno = 1;
    pthread_create(&((GLOBAL_hry + id_hry)->vlakno), 0, hry_smycka_vlakna, arg);

    return 0;
}

/**
 * Vytvoří herní smyčku.
 * Pošle vždy otázku připojeným hráčům a nachvíli se uspí, aby dostali prostor pro zaslání odpovědi.
 * Je zde spousta nepěkných složitých podmínek, kterí slouží k ověření, zda jsou hráči připojeni a čekají na otázku, aby nedošlo k záměně
 * klientů kvůli paraelnímu běhu.
 * Tento složitý složeným systém podmínek by šel nahradit zámkem, to by ale zase zkomplikovalo "sesypávání" klientů při odpojení.
 * @param arg
 * @return 
 */
void *hry_smycka_vlakna(void *arg) {
    int id_hry = *((int *) arg);
    int i;
    int fd_prvni = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->fd;
    int fd_druhej = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->fd;
    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu = 3;
    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->stav_stavoveho_diagramu = 3;
    for (i = 0; i < POCET_OTAZEK; i++) {

        if ((((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1) && (((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 3) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_prvni = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->fd;
            tcp_server_send_message(fd_prvni, (otazky + i)->text);
        }
        if ((((GLOBAL_hry + id_hry)->id_hrac_dva) != -1) && (((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_dva)))->stav_stavoveho_diagramu == 3) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_druhej = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->fd;
            tcp_server_send_message(fd_druhej, (otazky + i)->text);
        }

        usleep(10000000); //doba za kterou musí hráči odpovědět

        while (((((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1)&&((GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->zamek_odpovedi != 0)) || ((((GLOBAL_hry + id_hry)->id_hrac_dva) != -1)&&((GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->zamek_odpovedi != 0))) {
            usleep(10);
        }
        int odpoved_jedna = -1;
        int odpoved_dva = -1;
        printf ("skore hrac jedna %d\n", (GLOBAL_hry +id_hry)->score_hrac_jedna);
        printf("skore hrac dva %d \n", (GLOBAL_hry +id_hry)->score_hrac_dva);
        if (((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1) {
            (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->zamek_odpovedi = 1;
            (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->odpoved;
        }
        if (((GLOBAL_hry + id_hry)->id_hrac_dva) != -1) {
            (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->zamek_odpovedi = 1;
            odpoved_dva = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->odpoved;
        }
        hra_vyhodnot_odpoved(GLOBAL_hry + id_hry, (otazky + i)->odpoved, odpoved_jedna, odpoved_dva);

        if (((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1) {
            (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->odpoved = -1;
            (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->zamek_odpovedi = 0;
        }
        if (((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1) {
            (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->odpoved = -1;
            (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->zamek_odpovedi = 0;
        }

    }

    while (((GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->zamek_odpovedi != 0) || ((GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->zamek_odpovedi != 0)) {
        printf("zamek");
        usleep(10);
    }
    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->zamek_odpovedi = 1;
    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->zamek_odpovedi = 1;
    if ((GLOBAL_hry + id_hry)->score_hrac_jedna > (GLOBAL_hry + id_hry)->score_hrac_dva) {
        if ((((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1) && ((((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu ==3)) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_prvni = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->fd;
            tcp_server_send_message(fd_prvni, "5|1");
        }
        if ((((GLOBAL_hry + id_hry)->id_hrac_dva) != -1) && ((((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_dva)))->stav_stavoveho_diagramu ==3)) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_druhej = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->fd;
            tcp_server_send_message(fd_druhej, "5|2");
        }
    }
    else if  ((GLOBAL_hry + id_hry)->score_hrac_jedna < (GLOBAL_hry + id_hry)->score_hrac_dva) {
        if ((((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1) && ((((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 3)) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_prvni = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->fd;
            tcp_server_send_message(fd_prvni, "5|2");
        }
        if ((((GLOBAL_hry + id_hry)->id_hrac_dva) != -1) && ((((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_dva)))->stav_stavoveho_diagramu == 3)) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_druhej = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->fd;
            tcp_server_send_message(fd_druhej, "5|1");
        }
    } else {
        if ((((GLOBAL_hry + id_hry)->id_hrac_jedna) != -1) && ((((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 3)) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_prvni = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->fd;
            tcp_server_send_message(fd_prvni, "5|0");
        }
        if ((((GLOBAL_hry + id_hry)->id_hrac_dva) != -1) && ((((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_dva)))->stav_stavoveho_diagramu == 3)) || ((GLOBAL_klienti + (((GLOBAL_hry + id_hry)->id_hrac_jedna)))->stav_stavoveho_diagramu == 1))) {
            fd_druhej = (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->fd;
            tcp_server_send_message(fd_druhej, "5|0");

        }
    }


    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->zamek_odpovedi = 0;
    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->zamek_odpovedi = 0;
    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu = 1;
    (GLOBAL_klienti + (GLOBAL_hry + id_hry)->id_hrac_dva)->stav_stavoveho_diagramu = 1;

    hra_vyrezetuj_hru((GLOBAL_hry + id_hry));
    /* 
     (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_dva)->stav_stavoveho_diagramu=1;
      (GLOBAL_klienti + (GLOBAL_hry+id_hry)->id_hrac_jedna)->stav_stavoveho_diagramu=1;*/
    (GLOBAL_hry + id_hry)->stav = 0;
    
}
