#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "klient.h"
#include "klienti.h"
#include "hra.h"
#include "globalni_promenne.h"

int funkce (){
    return 0;
}

int klient_zaregiastruj_klienta(int id, char *jmeno, char *heslo){
    //zde nejprv musim uverit jeho unikatnost
    if ((GLOBAL_klienti + id)->stav_stavoveho_diagramu !=0){
        return -1; //nemelo by se stat neco je blbe, nekdo se prihlasuje kdyz nema
    }
    (GLOBAL_klienti + id)->jmeno_hrace = jmeno;
    (GLOBAL_klienti +id)->heslo = heslo;
    return 0;
    
}

int klient_znovu_prihlaseni(int fd, char *jmeno, char *heslo){
    int i;
    for (i =0; i<GLOBAL_pocet; i++){
        if ((strcmp(jmeno, (GLOBAL_klienti +i)->jmeno_hrace)== 0) && (strcmp(heslo, (GLOBAL_klienti +i)->heslo)==0) ){
            (GLOBAL_klienti + i)->stav_stavoveho_diagramu=1;
            (GLOBAL_klienti + i)->doba_necinosti = 0;
            (GLOBAL_klienti + i)->fd = fd;
             return 0; //overeni ok
        }
    }
     return -1; //overeni selhalo
   
}

int klienti_vrat_fd_klienta(char* jmeno_hrace){
    int fd;
    int navrat=klienti_vrat_id_klienta(jmeno_hrace);
    if (navrat == -1) {
        return navrat;
    }
    fd = (GLOBAL_klienti + navrat)->fd;
    printf("FD JE %d\n" , fd);
   
    return fd;
    return 5;
}

int klienti_vrat_id_klienta(char* jmeno_hrace){
   int i;
    for(i=0; i<GLOBAL_pocet; i++){
        if (strcmp((GLOBAL_klienti+i)->jmeno_hrace, jmeno_hrace) == 0){
            printf("POROVNAVANI %d \n",  i);
            return i;
        }
    }
   i=-1;
    return i;
    
}

int klienti_vrat_id_klienta_fd(int fd){
   int i;
   printf("pocet %d \n", GLOBAL_pocet);
    for(i=0; i<GLOBAL_pocet; i++){
        
        printf("fd je %d \n", (GLOBAL_klienti + i)->fd);
        if ((GLOBAL_klienti+i)->fd == fd){
            printf("POROVNAVANI %d \n",  fd);
            return i;
        }
    }
   i=-1;
    return i;
    
}

int klienti_pridej_klienta(int fd){
  //  (klienti+pocet)  = klient_vytvor_klienta(fd, jmeno_hrace);
    //kam, co , kolik
    
     klient s_kl;
     klient *kli = &s_kl;
     memset(kli, 0, sizeof(klient));
     klient_vytvor_klienta(kli, fd);
     
     memcpy((GLOBAL_klienti + GLOBAL_pocet), kli, sizeof(struct klient));
   
    
     GLOBAL_pocet++;
    printf("pridan hrac na pozici %d", GLOBAL_pocet );
    
    return 0;
   
}

/**
 * Odhlásí klienta - nastaví mu příznak že je odhlášený
 * @param id
 * @param fd
 * @param client_socks
 * @return 
 */
int klienti_odhlas_klienta(int id,int fd, fd_set *client_socks){
    (GLOBAL_klienti +id)->stav_stavoveho_diagramu = 5;
     close(fd);
    FD_CLR(fd, client_socks );
    return 0;
}

/**
 * Odebere klienta z pole klientu. Uplně ho tím pádem zapomene. Sesype klienty.
 * @param id
 * @param fd
 * @param client_socks
 * @return 
 */
int klienti_odeber_klienta(int id, int fd, fd_set *client_socks){
    int i;
     if ((GLOBAL_hry + (GLOBAL_klienti + id)->herni_mistnost)->id_hrac_dva == id) {
         (GLOBAL_hry + (GLOBAL_klienti + id)->herni_mistnost)->id_hrac_dva = -1; //taky tu musi bejt nejakej zamek urcite
     } else if ((GLOBAL_hry + (GLOBAL_klienti + id)->herni_mistnost)->id_hrac_jedna == id) {
         (GLOBAL_hry + (GLOBAL_klienti + id)->herni_mistnost)->id_hrac_jedna = -1;
     }
    if (strcmp((GLOBAL_klienti +id)->jmeno_hrace,"") != 0 ){
        printf("jmeno bude odebrano \n");
          globalni_promenne_odeber_jmeno((GLOBAL_klienti + id)->jmeno_hrace);
    }
    printf("neni jmeno k odebrani \n");
    
    for(i=id; i <GLOBAL_pocet-1; i++){
        //tady je asi chyba nebot zustane nekde ulozenej starej fd i po odpojeni*/
        memcpy(GLOBAL_klienti + i, GLOBAL_klienti + i+1, sizeof(struct klient));
        
    }
    close(fd);
    FD_CLR( fd, client_socks );
   // free(GLOBAL_klienti + GLOBAL_pocet -1);
    //zde na toho posledniho zavolam free
    GLOBAL_pocet--;
    
   
    return 0;
}
   
