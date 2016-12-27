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



#include "konstanty.h"
#include "klient.h"
#include "hry.h"
#include "hra.h"
#include "klienti.h"
#include "globalni_promenne.h"
#include <stdio.h>
#include <string.h>

int globalni_promenne_inicializace(){
     GLOBAL_pocet = 0;
    //GLOBAL_klienti=  malloc(sizeof(klient) * maxKlientu);
     GLOBAL_klienti = ( klient*)malloc(sizeof(klient) * MAX_KLIENTU);
     GLOBAL_hry = (hra*)malloc(sizeof(hra) * MAX_HER);
     
     return 0;
}