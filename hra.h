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


typedef
struct s_hra
{
    int id_hrac_jedna;
    int id_hrac_dva;
    int cislo_otazky;
    int score_hrac_jedna;
    int score_hrac_dva;
    int stav;
    int vlakno;
    
} s_hra;

int hra_vyrezetuj_hru(struct s_hra hra);

int hra_vyhodnot_odpoved(struct s_hra hra, int odpoved, int spravna_odpoved);



#endif /* HRA_H */
