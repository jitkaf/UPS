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
#include "hra.h"
#include <pthread.h>


int hry_prirad_do_hry(int id_hrac){
    int i;
    printf("jsem v metode hry_prirad_do_hry id hrace je %d \n", id_hrac);
    for (i=0; i<MAX_HER; i++){
        //v ifech nejaky zamek aby se to provedlo atomicky
        if ((GLOBAL_hry + i)->stav == 0){
            (GLOBAL_hry + i)->stav =1;
            (GLOBAL_hry + i)->id_hrac_jedna = id_hrac;
            printf("prida prvni hrac \n");
            return 0;
        }
        else if ((GLOBAL_hry + i)->stav == 1){ ///pridavam druheho hrace
            (GLOBAL_hry + i)->stav =2;
            (GLOBAL_hry + i)->id_hrac_dva = id_hrac;
            //ZDE BUDU JESTE TVORIT VLAKNO PRO HRU A HRA ZACNE
            printf("pridan druhy hrac \n");
            return 0;
        }
    }
    
    return -1; //signalizuje ze je plno
}