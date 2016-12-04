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

#include "globalni_promenne.h"


globalni_promenne_inicializace(){
    GLOBAL_pocet = 0;
    GLOBAL_klienti=  malloc(sizeof(klient) * maxKlientu);
}