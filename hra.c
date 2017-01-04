/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hra.c
 * Author: jitka
 * 
 * Created on 18. prosince 2016, 17:29
 */
#include "hra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int hra_vyrezetuj_hru(struct s_hra hra){
    //tady bude muset bejt nejakej zamek aby se to provedlo atomicky
    hra.stav  = 0;
    hra.id_hrac_jedna = 0;
    hra.id_hrac_dva = 0;
    hra.score_hrac_jedna =0;
    hra.cislo_otazky = 0;
    hra.score_hrac_dva =0;
}

int hra_vyhodnot_odpoved(struct s_hra hra, int odpoved, int spravna_odpoved){
    if (odpoved == spravna_odpoved){
       hra.score_hrac_jedna ++;
       return 1;
    }
    return 0;
}