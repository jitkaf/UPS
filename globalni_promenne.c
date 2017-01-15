/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   globalni_promenne.c
 * Author: jitka
 * 
 * Created on 2. prosince 2016, 10:25
 */


//#include <pthread.h>
#include "konstanty.h"
#include "globalni_promenne.h"

#include "klient.h"

#include "hra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * nastaví globální proměnné při spuštění programu
 */
int globalni_promenne_inicializace() {
    GLOBAL_pocet = 0;
    GLOBAL_klienti = (klient*) malloc(sizeof (klient) * MAX_KLIENTU);
    GLOBAL_hry = (s_hra*) malloc(sizeof (s_hra) * MAX_HER);

    GLOBAL_p_prvni = calloc(1, sizeof (s_seznam_jmen));
    GLOBAL_p_prvni->p_dalsi = NULL;
    GLOBAL_p_prvni->p_predchozi = NULL;
    return 0;
}

/**
 * Pridá jméno hráče do seznamu použitých jmen
 * @param jmeno
 * @return 
 */
int globalni_promenne_pridej_jmeno(char *jmeno) {
    int x;
    //  printf("jsem v int globalni_promenne_pridej_jmeno(char *jmeno) a jmeno je %s   a ohle: %s \n", jmeno, GLOBAL_p_prvni->jmeno);
    if (GLOBAL_p_prvni->jmeno == NULL) {
        GLOBAL_p_prvni->jmeno = calloc(MAX_DELKA_JMENA, 1);

        memcpy(GLOBAL_p_prvni->jmeno, jmeno, MAX_DELKA_JMENA);
        printf("přidávám jméno: %s \n", GLOBAL_p_prvni->jmeno);
    } else {//pridavam treti
        printf(" přidávám jméno: %s \n", GLOBAL_p_prvni->jmeno);
        struct s_seznam_jmen *pom = GLOBAL_p_prvni; //tady musim prekopirovavat!!!
        while (pom->p_dalsi != NULL) {
            x = strcmp(pom->jmeno, jmeno);
            if (x == 0) {
                return -1;
            }
            pom = pom->p_dalsi;
        }
        x = strcmp(pom->jmeno, jmeno);
        if (x == 0) {
            return -1;
        }
        struct s_seznam_jmen *p_nova = calloc(1, sizeof (s_seznam_jmen));
        p_nova->jmeno = calloc(MAX_DELKA_JMENA, 1);
        memcpy(p_nova->jmeno, jmeno, MAX_DELKA_JMENA);
        p_nova->p_dalsi = NULL;
        p_nova->p_predchozi = pom;
        pom->p_dalsi = p_nova;
        /*printf(" predposledn jmeno: %s \n", pom->jmeno);
        printf(" predposledn jmeno: %p \n", pom->p_dalsi);*/
    }
    return 0;
}

/**
 * vrati 1 pokud je prvni driv v abecede a dva pokud je druhej driv v abecede, nulu pokud jsou stejne
 * */
int globalni_promenne_porovnej_stringy(char *jeden, char* druhej) {
    int delka_j = sizeof (jeden);
    int delka_d = sizeof (druhej);
    int delka = 0;
    int i = 0;
    int vysledek = 0;
    if (delka_j < delka_d) {
        delka = delka_j;
    } else {
        delka = delka_d;
    }
    while ((vysledek == 0) &&(i < delka)) {
        if (jeden[i] < druhej[i]) {
            vysledek = 1;
        } else if (jeden[i] > druhej[i]) {
            vysledek = 2;
        }
    }
    if (vysledek == 0) {
        if (delka_j < delka_d) {
            vysledek = 1;
        } else if (delka_j > delka_d) {
            vysledek = 2;
        }
    }
    return vysledek;
}

/**
 * Odstrani jmeno ze seznamu použitych jmen
 */
int globalni_promenne_odeber_jmeno(char *jmeno) {
    struct s_seznam_jmen *pom = GLOBAL_p_prvni;
    while ((pom != NULL) && (strcmp(pom->jmeno, jmeno) != 0)) {
        pom = pom->p_dalsi;
    }

    if ((pom != NULL) &&(strcmp(pom->jmeno, jmeno) == 0)) {
        if (pom->p_predchozi == NULL) { //odstranuji prvni prvek
            if (pom->p_dalsi != NULL) { //neni jedina
                GLOBAL_p_prvni = pom->p_dalsi;
                GLOBAL_p_prvni->p_predchozi = NULL;
                if (GLOBAL_p_prvni->p_dalsi != NULL) {
                    GLOBAL_p_prvni->p_dalsi->p_predchozi = GLOBAL_p_prvni;
                }
            } else {//je jedina
                free(GLOBAL_p_prvni->jmeno);
                GLOBAL_p_prvni->jmeno = NULL;
            }

        } else if (pom->p_dalsi == NULL) { //odstranuji posledni co neni zaroven prvnim
            pom->p_predchozi->p_dalsi = NULL;
        } else { //je uprostred
            pom->p_predchozi->p_dalsi = pom->p_dalsi;
            pom->p_dalsi->p_predchozi = pom->p_predchozi;
        }
        //zde asi free(pom); - nebude musim ho dat ruzne aby minulo to kdy se jedna o jedine jmeno
    }

    return 0;
}