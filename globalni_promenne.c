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
#include "konstanty.h"
#include "klient.h"

#include "hra.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int globalni_promenne_inicializace(){
     GLOBAL_pocet = 0;
    //GLOBAL_klienti=  malloc(sizeof(klient) * maxKlientu);
     GLOBAL_klienti = ( klient*)malloc(sizeof(klient) * MAX_KLIENTU);
     GLOBAL_hry = (s_hra*)malloc(sizeof(s_hra) * MAX_HER);
     struct s_seznam_jmen *prvni = malloc(sizeof(s_seznam_jmen));
     prvni->jmeno = malloc(MAX_DELKA_JMENA);
     prvni->jmeno=NULL;
     prvni->p_predchozi=NULL;
     prvni->p_dalsi=GLOBAL_p_posledni;
     struct s_seznam_jmen *posledni = malloc(sizeof(s_seznam_jmen));
     posledni->jmeno = malloc(MAX_DELKA_JMENA);
     posledni->jmeno=NULL;
     posledni->p_dalsi=NULL;
     posledni->p_predchozi = prvni;
     
     return 0;
}

int globalni_promenne_pridej_jmeno(char *jmeno){
    int x;
  if(GLOBAL_p_prvni->jmeno == NULL){
      GLOBAL_p_prvni->jmeno = jmeno;
  }
  else if(GLOBAL_p_posledni->jmeno== NULL){
     x = globalni_promenne_porovnej_stringy(GLOBAL_p_prvni->jmeno, jmeno);
      if (x == 0){
          return -1; //jmeno obsazeno
      }
      else if (x == 1){
          GLOBAL_p_posledni->jmeno=jmeno;
      }
      else{
          GLOBAL_p_posledni=GLOBAL_p_prvni;
          GLOBAL_p_prvni->p_dalsi=GLOBAL_p_posledni;
          GLOBAL_p_prvni->jmeno = jmeno;
          GLOBAL_p_posledni->p_predchozi = GLOBAL_p_prvni;
          GLOBAL_p_posledni->p_dalsi=NULL;
      }
  }else{//pridavam treti
      struct s_seznam_jmen *pom = GLOBAL_p_prvni;
      while(pom->p_dalsi!=NULL){
           x = globalni_promenne_porovnej_stringy(pom->jmeno, jmeno);
           if (x == 0){
               return -1;
           }
           if(x == 2){
               struct s_seznam_jmen * nova = malloc(sizeof(struct s_seznam_jmen));
               nova->jmeno=malloc(sizeof(jmeno));
               nova->jmeno = jmeno;
               nova->p_predchozi = pom->p_predchozi;
               if (pom->p_predchozi!= NULL) {
                   pom->p_predchozi->p_dalsi=pom;
               }
               nova->p_dalsi = pom;
               return 0;
           }
           pom = pom->p_dalsi;
      }
  }
    return 0;
}

//vrati 1 pokud je prvni driv v abecede a dva pokud je druhej driv v abecede, nulu pokud jsou stejne
int globalni_promenne_porovnej_stringy(char *jeden, char* druhej){
    int delka_j=sizeof(jeden);
    int delka_d=sizeof(druhej);
    int delka =0;
    int i=0;
    int vysledek=0;
    if (delka_j<delka_d){
        delka = delka_j;
    }
    else{
        delka=delka_d;
    }
    while ((vysledek ==0) &&(i<delka)){
        if (jeden[i]<druhej[i]){
            vysledek=1;
        }
        else if(jeden[i]>druhej[i]){
            vysledek=2;
        }
    }
    if (vysledek ==0){
        if (delka_j<delka_d){
            vysledek =1;
        }
        else if (delka_j>delka_d){
            vysledek=2;
        }
    }
    return vysledek;
}

int globalni_promenne_odeber_jmeno(char *jmeno){
  struct  s_seznam_jmen *pom = GLOBAL_p_prvni;
   while ((pom!=NULL) && (strcmp(pom->jmeno, jmeno)!=0)){
      
       pom=pom->p_dalsi;
   }
   if ((pom!=NULL) &&(strcmp(pom->jmeno, jmeno) == 0)){
       if (pom->p_predchozi != NULL){
           pom->p_predchozi->p_dalsi = pom;        
       } 
       else{
           GLOBAL_p_prvni = pom;
           GLOBAL_p_prvni->p_dalsi =pom->p_dalsi;
       }
       if (pom->p_dalsi != NULL){
           pom->p_dalsi->p_predchozi=NULL;
       }
       else{
           GLOBAL_p_posledni = pom;
           GLOBAL_p_posledni->p_predchozi = pom->p_predchozi;
       }
   }
   
   return 0;
}