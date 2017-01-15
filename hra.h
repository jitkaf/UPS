/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hra.h
 * Author: jitka
 *
 * Created on 18. prosince 2016, 17:29
 */

#ifndef HRA_H
#define HRA_H
#include <pthread.h>

typedef
struct s_hra
{
    int id_hrac_jedna;
    int id_hrac_dva;
    int score_hrac_jedna;
    int score_hrac_dva;
    int stav;
    int prirazene_vlakno;
    pthread_t vlakno;
    
} s_hra;

int hra_poprve(int a, struct s_hra *hra);
int hra_vyrezetuj_hru(struct s_hra *hra);

int hra_vyhodnot_odpoved(struct s_hra *hra, int spravna_odpoved, int odpoved_jedna, int odpoved_dva);



#endif /* HRA_H */
