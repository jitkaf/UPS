/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   herni_otazky.c
 * Author: jitka
 * 
 * Created on 5. ledna 2017, 11:15
 */

#include "herni_otazky.h"
#include "konstanty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int herni_otazky_nacti_otazky(){
    otazky = calloc(10,sizeof(struct s_otazka));
    int i;
    for(i=0; i<10;i++){
        (otazky+i)->text=calloc(DELKA_OZAZKY,1);
        
    }
    
    (otazky)->id_otazky=1;
    (otazky)->odpoved=3;
    memcpy((otazky)->text, "Kolik je dni v tydnu?|4|5|7",27);

    (otazky + 1)->id_otazky=2;
    (otazky + 1)->odpoved=1;
    memcpy((otazky + 1)->text, "Prvni mesic v roce je:|leden|unor|brezen",39);
    
    (otazky + 2)->id_otazky=3;
    (otazky + 2)->odpoved=2;
    memcpy((otazky + 2)->text, "Jahoda je:|zelenina|ovoce|jablko",32);
    
    (otazky + 3)->id_otazky=4;
    (otazky+ 3)->odpoved=3;
    memcpy((otazky + 3)->text, "Kolik ma leden dni?|29|31|30",28);
    
    (otazky + 4)->id_otazky=5;
    (otazky + 4)->odpoved=1;
    memcpy((otazky + 4)->text, "Prezident Ceske republiky je:|Zeman|Trump|Gott",45);
    
    (otazky + 5)->id_otazky=6;
    (otazky + 5)->odpoved=1;
    memcpy((otazky + 5)->text, "Prvni den v tynu je:|pondeli|utery|streda",41);
    
    (otazky + 6)->id_otazky=7;
    (otazky+ 6)->odpoved=3;
    memcpy((otazky + 6)->text, "Posledni den v tydnu je:|ctvrtek|patek|nedele",45);
    
    (otazky + 7)->id_otazky=8;
    (otazky + 7)->odpoved=3;
    memcpy((otazky + 7)->text, "Vanoce jsou v:|srpnu|dubnu|prosinci",35);
    
    (otazky + 8)->id_otazky=9;
    (otazky + 8)->odpoved=2;
    memcpy((otazky + 8)->text, "Zmrzla voda je:|ohen|led|savo",29);
    
    (otazky + 9)->id_otazky=10;
    (otazky + 9)->odpoved=1;
    memcpy((otazky + 9)->text, "Knihy si lze pujcit v:|knihovne|knihkupectvi|bance",50);
    
  
    
    
    
    return 0;
}