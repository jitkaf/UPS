/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hry.h
 * Author: jitka
 *
 * Created on 18. prosince 2016, 18:35
 */

#ifndef HRY_H
#define HRY_H

int hry_prirad_do_hry(int id_hrac);
int hry_vytvor_vlakno_hry(int i);
void *hry_smycka_vlakna( void *arg );


#endif /* HRY_H */
