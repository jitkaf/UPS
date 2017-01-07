/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   herni_otazky.h
 * Author: jitka
 *
 * Created on 5. ledna 2017, 11:15
 */

#ifndef HERNI_OTAZKY_H
#define HERNI_OTAZKY_H

struct s_otazka{
    int id_otazky;
    int odpoved;
    char *text;  
}s_otazka;

struct s_otazka* otazky;

int herni_otazky_nacti_otazky();
/*int herni_otazky_losuj_otazku();
int herni_otazky_odpoved(int id_otazky);
char *herni_otazky_text(int id_otazky);*/



#endif /* HERNI_OTAZKY_H */
