/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   zpracovavac_zprav.h
 * Author: jitka
 *
 * Created on 15. listopadu 2016, 8:41
 */

#ifndef ZPRACOVAVAC_ZPRAV_H
#define ZPRACOVAVAC_ZPRAV_H

struct s_zprava{
    char *prvni_cast;
    char *druha_cast;
    char *treti_cast;
    int q;
}s_zprava;

int zpracovavac_zprav_vyhodnot_zpravu(int fd, char * msg, int delka);

int zpracovavac_zprav_parser(struct s_zprava *p_zprava, char * msg, int delka);

int zpracovavac_zprav_registrace(int fd, struct s_zprava * p_zprava);

int zpracovavac_zprav_znovu_pripojeni(int fd,struct s_zprava *p_zprava);

int zpracovavac_zprav_start(int fd,struct s_zprava *p_zprava) ;

int zpracovavac_zprav_odpoved(int fd,struct s_zprava *p_zprava);

int zpracovavac_zprav_odpoj(int fd,struct s_zprava *p_zprava);


int zpracovavac_zprav_pokus_opetovne_pripojeni(int fd, char *msg);

int zpracovavac_zprav_posli_zpet(int fd, char *msg);

int zpracovavac_zprav_posli_vsem(int fd, char *msg);

#endif /* ZPRACOVAVAC_ZPRAV_H */
