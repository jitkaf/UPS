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


int zpracovavac_zprav_vyhodnot_zpravu(int fd, char * msg, struct klient* klienti);

int zpracovavac_zprav_pokus_opetovne_pripojeni(int fd, char *msg,  struct klient* klienti);

int zpracovavac_zprav_posli_zpet(int fd, char *msg, struct klient * klienti);

int zpracovavac_zprav_posli_vsem(int fd, char *msg, struct klient *klienti);

#endif /* ZPRACOVAVAC_ZPRAV_H */
