/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   globalni_promenne.h
 * Author: jitka
 *
 * Created on 2. prosince 2016, 10:25
 */

#ifndef GLOBALNI_PROMENNE_H
#define GLOBALNI_PROMENNE_H
#include <pthread.h>

struct s_seznam_jmen{
    char *jmeno;
    struct s_seznam_jmen* p_dalsi;
    struct s_seznam_jmen* p_predchozi; 
}s_seznam_jmen;

struct s_seznam_jmen *GLOBAL_p_prvni;
//struct s_seznam_jmen *GLOBAL_p_posledni;


int GLOBAL_pocet;
//klient GLOBAL_klienti[maxKlientu];

struct s_hra * GLOBAL_hry;
struct klient * GLOBAL_klienti; 

pthread_t GLOBAL_vlakna[10];

int globalni_promenne_inicializace();
int globalni_promenne_pridej_jmeno(char *jmeno);
int globalni_promenne_porovnej_stringy(char *jeden, char* druhej);
int globalni_promenne_odeber_jmeno(char *jmeno);

#endif /* GLOBALNI_PROMENNE_H */
