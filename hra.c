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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hra.h"
#include "globalni_promenne.h"

int hra_vyrezetuj_hru(int id_hry){
    //tady bude muset bejt nejakej zamek aby se to provedlo atomicky
    (GLOBAL_hry +id_hry)->stav  = 0;
    (GLOBAL_hry +id_hry)->id_hrac_jedna = 0;
    (GLOBAL_hry +id_hry)->id_hrac_dva = 0;
    (GLOBAL_hry +id_hry)->score_hrac_jedna =0;
    (GLOBAL_hry +id_hry)->cislo_otazky = 0;
    (GLOBAL_hry +id_hry)->score_hrac_dva =0;
}

int hra_vyhodnot_odpoved(int id_hry, int odpoved, int spravna_odpoved){
    if (odpoved == spravna_odpoved){
       (GLOBAL_hry +id_hry)->score_hrac_jedna ++;
       return 1;
    }
    return 0;
}