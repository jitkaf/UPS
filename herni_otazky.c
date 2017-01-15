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

/**
 * Vytvoří herní otázky
 */
int herni_otazky_nacti_otazky() {
    otazky = calloc(10, sizeof (struct s_otazka));
    int i;
    for (i = 0; i < 10; i++) {
        (otazky + i)->text = calloc(DELKA_OZAZKY, 1);
    }

    (otazky)->id_otazky = 1;
    (otazky)->odpoved = 3;
    memcpy((otazky)->text, "8|Kolik je dní v týdnu?|4|5|7", 31);

    (otazky + 1)->id_otazky = 2;
    (otazky + 1)->odpoved = 1;
    memcpy((otazky + 1)->text, "8|První měsíc v roce je:|leden|únor|březen", 47);

    (otazky + 2)->id_otazky = 3;
    (otazky + 2)->odpoved = 2;
    memcpy((otazky + 2)->text, "8|Jahoda je:|zelenina|ovoce|jablko", 34);

    (otazky + 3)->id_otazky = 4;
    (otazky + 3)->odpoved = 3;
    memcpy((otazky + 3)->text, "8|Kolik má leden dní?|29|31|30", 32);

    (otazky + 4)->id_otazky = 5;
    (otazky + 4)->odpoved = 1;
    memcpy((otazky + 4)->text, "8|Prezident České republiky je:|Zeman|Trump|Gott", 50);

    (otazky + 5)->id_otazky = 6;
    (otazky + 5)->odpoved = 1;
    memcpy((otazky + 5)->text, "8|První den v týdnu je:|pondělí|úterý|středa", 50);

    (otazky + 6)->id_otazky = 7;
    (otazky + 6)->odpoved = 3;
    memcpy((otazky + 6)->text, "8|Poslední den v týdnu je:|čtvrtek|pátek|neděle", 57);

    (otazky + 7)->id_otazky = 8;
    (otazky + 7)->odpoved = 3;
    memcpy((otazky + 7)->text, "8|Vánoce jsou v:|srpnu|dubnu|prosinci", 38);

    (otazky + 8)->id_otazky = 9;
    (otazky + 8)->odpoved = 2;
    memcpy((otazky + 8)->text, "8|Zmrzlá voda je:|oheň|led|savo", 33);

    (otazky + 9)->id_otazky = 10;
    (otazky + 9)->odpoved = 1;
    memcpy((otazky + 9)->text, "8|Knihy si lze půjčit v:|knihovně|knihkupectví|bance", 56);

    return 0;
}