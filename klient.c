#include "klient.h"
#include "konstanty.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**Vytvoří strukturu pro klienta*/
int klient_vytvor_klienta(struct klient *kli, int fd) {
 kli->doba_necinosti = 0;
    kli->fd = fd;
    kli->herni_mistnost = -1;
    kli->jmeno_hrace = calloc(MAX_DELKA_JMENA, 1);
    memcpy(kli->jmeno_hrace, "", 1);
    kli->heslo = calloc(MAX_DELKA_JMENA, 1);
    kli->skore = 0;

    kli->odpoved = 0;
    kli->stav_stavoveho_diagramu = 0;
    kli->zamek_odpovedi = 0;
    kli->pocet_vadnych_zprav = 0;
    printf("Vytářím hráče se zatím neznámým jménem a s fd %d \n", fd);
    return 0;
}

/**
 * Vynuluje dobu nečinosti hráče
 * @param hrac
 * @return 
 */
int klient_vynuluj_dobu_necinosti(struct klient hrac) {
    hrac.doba_necinosti = 0;
    return 0;
}

/**
 * Zvětší dobu nečinosti hráče
 * @param hrac
 * @return 
 */
int klient_inkrementuj_dobu_necinosti(struct klient hrac) {
    hrac.doba_necinosti++;
    return 0;
}

/**
 * Přiřadí hráči herní mísnost
 * @param hrac
 * @param mistnost
 * @return 
 */
int klient_prirad_herni_mistnost(struct klient hrac, int mistnost) {
    hrac.herni_mistnost = mistnost;
    return 0;
}

/**
 * Odebere hráči herní mísnost
 * @param hrac
 * @return 
 */
int klient_odeber_herni_misnost(struct klient hrac) {
    hrac.herni_mistnost = -1;
    return 0;
}

/**
 * Nastaví klientovi příznak odpojení
 * @param hrac
 * @return 
 */
int klient_odpoj(struct klient hrac) {
    hrac.stav_stavoveho_diagramu = 5;
    return 0;
}

/**
 * Připojí klienta
 * @param hrac
 * @return 
 */
int klient_pripoj(struct klient hrac) {
    hrac.doba_necinosti = 0;
    hrac.stav_stavoveho_diagramu = 1;

    return 0;
}

/**
 * Nepoužívaná bonusová metoda
 * @return 
 */
int klient_generuj_heslo() {
    //bude vylepseno :)

    return 5;
}

/**
 * Nastaví odpověď hráče na to co od něj přišlo jako odpověď
 * @param hrac
 * @param odpoved
 * @return 
 */
int klient_nastav_odpoved(struct klient hrac, int odpoved) {
    if (hrac.zamek_odpovedi == 0) { // z vlakna nikdo necte, pokud ano, uz je pozde a odpoved se nezpracovava, jen si ulozim dobu necinosti hrace a nulu
        hrac.zamek_odpovedi = 1;
        if (hrac.odpoved = 0) {
            hrac.doba_necinosti++;

        } else {
            hrac.odpoved = 0;
            hrac.doba_necinosti = 0;

        }
        hrac.zamek_odpovedi = 0;
    } else {
        hrac.doba_necinosti = 0;
    }
    return 0;
}

/**
 * Vrátí odpověd hráče
 * @param hrac
 * @return 
 */
int klient_dej_odpoved_hrace(struct klient hrac) {
    int pom;
    if (hrac.zamek_odpovedi == 0) {
        hrac.zamek_odpovedi = 1;
        pom = hrac.odpoved;
        hrac.odpoved = 0;
        hrac.zamek_odpovedi = 0;
        return pom;
    }
    return -1; //signaulizuje ze nelze zrovna cist odpoved hrace
}