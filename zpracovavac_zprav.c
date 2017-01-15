#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

#include "zpracovavac_zprav.h"

#include "tcp_server.h"
#include "klient.h"
#include "globalni_promenne.h"
#include "hra.h"
#include "konstanty.h"
#include "klienti.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//identifikator_sluzby|sve_id|sve_jmeno|zprava    : c|cc|zzzzzzzzzz|zzzzzzzzz......

/**
 * Vyhodnotí zprávu
 * @param fd
 * @param msg
 * @param delka
 * @param client_socks
 * @return 
 */
int zpracovavac_zprav_vyhodnot_zpravu(int fd, char * msg, int delka, fd_set *client_socks) {
    int pom;
  //  printf("jsem v zpracovavac_zprav_vyhodnot_zpravu se zpravou %s o delce %d \n", msg, delka);
    struct s_zprava zprava;
    struct s_zprava *p_zprava = &zprava;
 zpracovavac_zprav_parser(p_zprava, msg, delka);
   if (strcmp(p_zprava->prvni_cast, "0") == 0) {
        //zadost o registraci  overit ze je jmeno volne
        printf("jej 0 \n");
        zpracovavac_zprav_registrace(fd, p_zprava);

    } else if (strcmp(p_zprava->prvni_cast, "1") == 0) {
        //zadost o znovu pripojeni - overit jestli je klient ve stavu 5 
        zpracovavac_zprav_znovu_prihlaseni(fd, p_zprava);
    } else if (strcmp(p_zprava->prvni_cast, "2") == 0) {
        //chce zacit hrat, overit zda je ve stavu 1
        zpracovavac_zprav_start(fd, p_zprava);

    } else if (strcmp(p_zprava->prvni_cast, "3") == 0) {
        //chce odpovedet na otazku, overit zda je ve stavu 3  2
        zpracovavac_zprav_odpoved(fd, p_zprava);

    } else if (strcmp(p_zprava->prvni_cast, "4") == 0) {
        printf("kuk");
        //zadost o odpojeni, zkoumat zda uplne nebo jen odhlasit
        zpracovavac_zprav_odpoj(fd, p_zprava, client_socks);

    } else {
        //posila nejake kraviny
        zpracovavac_zprav_nesmysly(fd, client_socks);

    }

    return 0;
}

/**
 * Vhodne rozparsuje zprávu.
 * @param p_zprava
 * @param msg
 * @param delka
 * @return 
 */
int zpracovavac_zprav_parser(struct s_zprava *p_zprava, char * msg, int delka) {
    printf("jsem v parseru se zpravou: %s o delce: %d \n", msg, delka);
    // klient* kli = (klient*) malloc(sizeof(klient));
    // struct s_zprava * p_zpr =calloc(1,sizeof(s_zprava));

    p_zprava->prvni_cast = calloc(1, 1);
    p_zprava->druha_cast = calloc(MAX_DELKA_JMENA, 1);
    p_zprava->treti_cast = calloc(MAX_DELKA_JMENA, 1);

    int i = 0;
    int j = 0;
    while ((i < delka - 1)&&(msg[i] != '|')) {
        i++;
    }
    if (i == 0) {

        p_zprava->prvni_cast[0] = '-';
        p_zprava->druha_cast[0] = '-';
        p_zprava->treti_cast[0] = '-';
    } else {
        memcpy(p_zprava->prvni_cast, msg, i);
        i++;
        j = i;


        while ((i < delka - 1)&&(msg[i] != '|')) {
            i++;
            // printf("icko dva je %d \n", i);
        }
        if (i == j) {
            p_zprava->druha_cast[0] = '-';
            p_zprava->treti_cast[0] = '-';
        } else {
            memcpy(p_zprava->druha_cast, msg + j, i - j);
           
            i++;
            j = i;

            while ((i < delka - 1)&&(msg[i] != '|')) {
                i++;
            }
            if (i == j) {

                p_zprava->treti_cast[0] = '-';
            } else {
                memcpy(p_zprava->treti_cast, msg + j, i - 1);
                //     printf("treti cas prijate zpravy je: %s \n", p_zprava->treti_cast);
            }
        }
    }
    printf("prvni cast prijate zpravy je: %s \n", p_zprava->prvni_cast);
    printf("druha cast prijate zpravy je: %s \n", p_zprava->druha_cast);
    printf("treti cast prijate zpravy je: %s \n", p_zprava->treti_cast);
    return 0;
}

/**
 * Reaguje na požadavek na registraci hráče
 * @param fd
 * @param p_zprava
 * @return 
 */
int zpracovavac_zprav_registrace(int fd, struct s_zprava * p_zprava) {
    printf("zpracovavac_zprav_registrace");
    if (strcmp(p_zprava->druha_cast, "-") == 0) {
        //poslat jmeno nezadano
        tcp_server_send_message(fd, "0|1");
    } else if (strcmp(p_zprava->treti_cast, "-") == 0) {
        //poslat jmeno nezadano
        tcp_server_send_message(fd, "0|2");
    } else {
        //zkontrolovat zda jmeno uz existuje int

        int id = klienti_vrat_id_klienta_fd(fd);
      //  printf("id je %d \n", id);
        if (id == -1) {
            klienti_pridej_klienta(fd);
            id = klienti_vrat_id_klienta_fd(fd);
        }
        else if ((((GLOBAL_klienti + id)->stav_stavoveho_diagramu) != 0) &&((GLOBAL_klienti + id)->stav_stavoveho_diagramu != 5)) {
            tcp_server_send_message(fd, "9|0");
            return 0;
        }

        (GLOBAL_klienti + id)->pocet_vadnych_zprav = 0;
        if (globalni_promenne_pridej_jmeno(p_zprava->druha_cast) == -1) {
          tcp_server_send_message(fd, "0|3");

        } else {
           strcpy((GLOBAL_klienti + id)->jmeno_hrace, p_zprava->druha_cast);
            strcpy((GLOBAL_klienti + id)->heslo, p_zprava->treti_cast);
            (GLOBAL_klienti + id)->stav_stavoveho_diagramu = 1;
            tcp_server_send_message(fd, "0|0");
        }
    }

    return 0;
}

int zpracovavac_zprav_znovu_prihlaseni(int fd, struct s_zprava *p_zprava) {
    int id = klienti_vrat_id_klienta((p_zprava->druha_cast));
    if (id == -1) {
        tcp_server_send_message(fd, "1|1");
        (GLOBAL_klienti + id)->pocet_vadnych_zprav++;
        return -1;
    }
    if (strcmp(p_zprava->treti_cast, (GLOBAL_klienti + id)->heslo) == 0) {
        if ((GLOBAL_klienti + id)->stav_stavoveho_diagramu == 5){
            (GLOBAL_klienti + id)->stav_stavoveho_diagramu = 1;
            (GLOBAL_klienti + id)->pocet_vadnych_zprav = 0;
            tcp_server_send_message(fd, "1|0"); //ze je ok zaregistrovanej
        }
        else{
            tcp_server_send_message(fd, "1|3");
        }
        
    } else {
        (GLOBAL_klienti + id)->pocet_vadnych_zprav++;
        tcp_server_send_message(fd, "1|1"); //chyba jmena nebo hesla 
    }

    return 0;
}

/**
 * Zpracuje požadavek o začátek hry
 * @param fd
 * @param p_zprava
 * @return 
 */
int zpracovavac_zprav_start(int fd, struct s_zprava *p_zprava) {
    int id = klienti_vrat_id_klienta_fd(fd);
    if ((id == -1) || ((GLOBAL_klienti + id)->stav_stavoveho_diagramu != 1)) {
        (GLOBAL_klienti + id)->pocet_vadnych_zprav++;

        tcp_server_send_message(fd, "9|0");
        return -1;
    } else {
        (GLOBAL_klienti + id)->pocet_vadnych_zprav = 0;
        (GLOBAL_klienti + id)->stav_stavoveho_diagramu = 2; //overit ze dva je pripraven na hru
        hry_prirad_do_hry(id);
        tcp_server_send_message(fd, "2|0");
    }
    return 0;
}

int zpracovavac_zprav_odpoved(int fd, struct s_zprava *p_zprava) {
    int id = klienti_vrat_id_klienta_fd(fd);
    int odpoved = -1;

    if (id == -1) {
        tcp_server_send_message(fd, "9");
        return -1;
    }

    if (((GLOBAL_klienti + id)->stav_stavoveho_diagramu == 3)&&((GLOBAL_klienti + id)->zamek_odpovedi == 0)) {
        (GLOBAL_klienti + id)->zamek_odpovedi = 1;

        if (p_zprava->druha_cast[0] == '1') {
            (GLOBAL_klienti + id)->pocet_vadnych_zprav = 0;
            odpoved = 1;
        } else if (p_zprava->druha_cast[0] == '2') {
            (GLOBAL_klienti + id)->pocet_vadnych_zprav = 0;
            odpoved = 2;
        } else if (p_zprava->druha_cast[0] == '3') {
            (GLOBAL_klienti + id)->pocet_vadnych_zprav = 0;
            odpoved = 3;
        }
        //zde musim prevest na int
        (GLOBAL_klienti + id)->odpoved = odpoved;
        //mozna davad vedet ze odpoved prijata nebo dalsi veci
        tcp_server_send_message(fd, "3|0");
        (GLOBAL_klienti + id)->zamek_odpovedi = 0;
    } else {
        tcp_server_send_message(fd, "3|1");
    }

   return 0;
}

/**
 * Zpracuje požadavek o odpojení
 * @param fd
 * @param p_zprava
 * @param client_socks
 * @return 
 */
int zpracovavac_zprav_odpoj(int fd, struct s_zprava *p_zprava, fd_set *client_socks) {
    int id = klienti_vrat_id_klienta_fd(fd);
    if (id == -1) {
        tcp_server_send_message(fd, "9");
        return -1;
    }

    if (strcmp(p_zprava->druha_cast, "0") == 0) {
        //uplne idpojeni a zapomenuti 
        //DOPLNIT O OODSTRANENI JMENA ZE SEZNAMU

       
        klienti_odeber_klienta(id, fd, client_socks);

    }
    if (strcmp(p_zprava->druha_cast, "1") == 0) {
        (GLOBAL_klienti + id)->pocet_vadnych_zprav = 0;
        (GLOBAL_klienti + id)->stav_stavoveho_diagramu = 5;

        tcp_server_send_message(fd, "4|0");
        klienti_odhlas_klienta(id, fd, client_socks);
    }
    return 0;
}

/**
 * Reaguje na nysmysly posílane od klienta 
 * @param fd
 * @param client_socks
 * @return 
 */
int zpracovavac_zprav_nesmysly(int fd, fd_set *client_socks) {
    int id = klienti_vrat_id_klienta_fd(fd);
    if (id == -1) {
        klienti_pridej_klienta(fd);
        id = klienti_vrat_id_klienta_fd(fd);
    }
    (GLOBAL_klienti + id)->pocet_vadnych_zprav++;
    if ((GLOBAL_klienti + id)->pocet_vadnych_zprav > TOLERANCE) {
        tcp_server_send_message(fd, "9|1");
        klienti_odeber_klienta(id, fd, client_socks);
        printf("Klient s fd %d odpojen za nevhodne chovani. \n", fd);
    } else {
        tcp_server_send_message(fd, "9|0");
        printf("Klient s fd %d posilal neplatnou zpravu. \n", fd);
    }
}

int zpracovavac_zprav_posli_zpet(int fd, char *msg) {
    int delka = strlen(msg);
    printf("v metode prijata yprava je %s \n", msg);
    int vel = delka - 15;
    char * zprava = (char*) malloc(vel);
    memcpy(zprava, msg + 15, delka - 15);
    tcp_server_send_message(fd, zprava);
    // free(zprava);
    return 0;
}

int zpracovavac_zprav_posli_vsem(int fd, char *msg) {
    int delka = strlen(msg);
    int i;
    int vel = delka - 15;
    char * zprava2 = (char*) malloc(vel);
    memcpy(zprava2, msg + 15, delka - 15);
    //printf("-----------cislo------- %d \n", pocet);
    for (i = 0; i < GLOBAL_pocet; i++) {
        printf("posilam a i je %d", i);
        if ((GLOBAL_klienti + i)->stav_stavoveho_diagramu == 5) {
            tcp_server_send_message((GLOBAL_klienti + i)->fd, zprava2);
        }
    }
    // free(zprava2);
    return 0;
}