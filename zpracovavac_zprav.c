
#include "zpracovavac_zprav.h"

#include "tcp_server.h"
#include "klient.h"
#include "globalni_promenne.h"
#include "hra.h"
#include "konstanty.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//identifikator_sluzby|sve_id|sve_jmeno|zprava    : c|cc|zzzzzzzzzz|zzzzzzzzz......
int zpracovavac_zprav_vyhodnot_zpravu(int fd, char * msg, int delka){
   int pom;
   printf("jsem v zpracovavac_zprav_vyhodnot_zpravu se zpravou %s o delce %d \n", msg, delka) ;
  //struct s_zprava *p_zprava = malloc(sizeof(s_zprava));
   struct s_zprava zprava;
   struct s_zprava *p_zprava = &zprava;
  
  zpracovavac_zprav_parser(p_zprava, msg,delka);
 //strcpy( p_zprava, zpracovavac_zprav_parser( msg,delka));
  

  
  if (strcmp(p_zprava->prvni_cast, "0")==0){
      //zadost o registraci  overit ze je jmeno volne
      printf("jej 0 \n");
      zpracovavac_zprav_registrace(fd, p_zprava);
     
  }
  else if (strcmp(p_zprava->prvni_cast, "1") == 0 ){
      //zadost o znovu pripojeni - overit jestli je klient ve stavu 5 
      zpracovavac_zprav_znovu_pripojeni( fd, p_zprava);
  }
  else if (strcmp(p_zprava->prvni_cast, "2") == 0 ){
      //chce zacit hrat, overit zda je ve stavu 1
      zpracovavac_zprav_start(fd, p_zprava) ;
      
  }
  else if (strcmp(p_zprava->prvni_cast, "3") == 0 ){
      //chce odpovedet na otazku, overit zda je ve stavu 3  2
      zpracovavac_zprav_odpoved(fd, p_zprava);
      
  }
  else if (strcmp(p_zprava->prvni_cast, "4") == 0 ){
      printf("kuk");
      //zadost o odpojeni, zkoumat zda uplne nebo jen odhlasit
      zpracovavac_zprav_odpoj(fd, p_zprava);
      
  }
  else if (strcmp(p_zprava->prvni_cast, "5") == 0 ){
      //chce prejit z 5 do 1, overit zda je v 5
      
  }
   /*
    switch (msg[0]){
        case '1':  //pripojovani ztraceneho klienta
            if(msg[1]=='|'){
                printf("jdu na to");
                zpracovavac_zprav_pokus_opetovne_pripojeni(fd, msg);
            }
            break;
        
        
        
        
        case 'a':  //pripojovani ztraceneho klienta
            if(msg[1]=='|'){
                printf("jdu na to");
                zpracovavac_zprav_pokus_opetovne_pripojeni(fd, msg);
            }
            break;
        case 'b': 
            if(msg[1]=='|'){
                zpracovavac_zprav_posli_zpet(fd, msg) ;
            }
            break;
        case 'c': //broadcast
            if (msg[1]=='|'){
                zpracovavac_zprav_posli_vsem(fd, msg);
            }
            break;
        case 'd': //odpojit klienta
            if (msg[1]=='|'){
                
            }
            break;
     }
        
    */
    return 0;
}


int zpracovavac_zprav_parser( struct s_zprava *p_zprava, char * msg, int delka){
    printf("jsem v parseru se zpravou: %s o delce: %d \n", msg, delka);
    // klient* kli = (klient*) malloc(sizeof(klient));
   // struct s_zprava * p_zpr =calloc(1,sizeof(s_zprava));
    
    p_zprava->prvni_cast = calloc(1, 1);
    p_zprava->druha_cast = calloc( MAX_DELKA_JMENA,1);
    p_zprava->treti_cast = calloc(MAX_DELKA_JMENA,1);
    
    int i=0;
    int j=0;
    while ((i<delka-1)&&(msg[i]!='|')){
        i++;
        //printf("icko je %d \n", i);
    }
    if (i==0){
        
        p_zprava->prvni_cast[0] = '-';
        p_zprava->druha_cast[0] = '-';
        p_zprava->treti_cast[0] = '-';
    }
    else {
      //  printf("jej\n" );
        printf("icko je: %d \n" , i);
        memcpy(p_zprava->prvni_cast,msg, i);
        printf("prvni cas prijate zpravy je: %s \n", p_zprava->prvni_cast);
         printf("\n -0-    %d   %d", sizeof(p_zprava->prvni_cast), 1);
         printf("\n dd \n");
        i++;
        j=i;
      
    
        while ((i<delka-1)&&(msg[i]!='|')){
            i++;
           // printf("icko dva je %d \n", i);
        }
         if (i==j){
             p_zprava->druha_cast[0] = '-';
            p_zprava->treti_cast[0] = '-';
        }
        else {
           memcpy(p_zprava->druha_cast,msg + j, i-j);
           // printf("druha cas prijate zpravy je: %s \n", p_zprava->druha_cast);

            i++;
            j=i;
            
            while ((i<delka-1)&&(msg[i]!='|')){
                i++;
              //  printf("icko tri je %d \n", i);
            }
            if (i==j){
                 
                 p_zprava->treti_cast[0] = '-';
            }
            else {
               memcpy(p_zprava->treti_cast,msg +j , i-1);
           //     printf("treti cas prijate zpravy je: %s \n", p_zprava->treti_cast);
            }
        }
    }
    printf("prvni cast prijate zpravy je: %s \n", p_zprava->prvni_cast);
    printf("druha cast prijate zpravy je: %s \n", p_zprava->druha_cast);
    printf("treti cast prijate zpravy je: %s \n", p_zprava->treti_cast);
    return 0;
}

int zpracovavac_zprav_registrace(int fd, struct s_zprava * p_zprava){
    printf("zpracovavac_zprav_registrace");
      if(strcmp(p_zprava->druha_cast, "-") == 0 ){
          //poslat jmeno nezadano
          tcp_server_send_message(fd, "0|1", 3 );
      }
      else if(strcmp(p_zprava->treti_cast, "-") == 0 ){
          //poslat jmeno nezadano
          tcp_server_send_message(fd, "0|2", 3 );
      }
      else{
          //zkontrolovat zda jmeno uz existuje int
         int id = klienti_vrat_id_klienta_fd(fd);
         printf("id je %d \n", id);
          if (id == -1){
              klienti_pridej_klienta(fd);
              id = klienti_vrat_id_klienta_fd(fd);
         } 
         if (globalni_promenne_pridej_jmeno(p_zprava->druha_cast) == -1){
             printf("kuk");
             tcp_server_send_message(fd, "0|3", 3 );
         
         }
         else{
             printf("globalik %s \n", (GLOBAL_klienti + id)->jmeno_hrace);
             strcpy((GLOBAL_klienti + id)->jmeno_hrace, p_zprava->druha_cast);
             strcpy((GLOBAL_klienti + id)->heslo, p_zprava->treti_cast);
             (GLOBAL_klienti +id)->stav_stavoveho_diagramu =1;
             tcp_server_send_message(fd, "0|0", 3 );
         }
      }
 
 return 0;
}

int zpracovavac_zprav_znovu_pripojeni(int fd,struct s_zprava *p_zprava){
    int id = klienti_vrat_id_klienta_fd(fd);
    if (id == -1){
        tcp_server_send_message(fd, "9", 1);
        return -1;
    }
    
    if ((strcmp(p_zprava->druha_cast, (GLOBAL_klienti +id)->jmeno_hrace) == 0) && (strcmp(p_zprava->treti_cast, (GLOBAL_klienti +id)->heslo) == 0)){
        (GLOBAL_klienti +id)->stav_stavoveho_diagramu=1;
        tcp_server_send_message(fd,"1|0",3);   //ze je ok zaregistrovanej
    }
    else{
       tcp_server_send_message(fd,"1|1",3); //chyba jmena nebo hesla 
    }
    
    return 0 ;
}

int zpracovavac_zprav_start(int fd,struct s_zprava *p_zprava){
    int id = klienti_vrat_id_klienta_fd(fd);
    printf(" id ve start je %d    a fd je %d a stav: %d\n", id, fd, (GLOBAL_klienti +id)->stav_stavoveho_diagramu);
    if((id == -1) || ((GLOBAL_klienti +id)->stav_stavoveho_diagramu != 1)){
        tcp_server_send_message(fd, "9",1);
        return -1;
    }
    else{
        (GLOBAL_klienti +id)->stav_stavoveho_diagramu = 2; //overit ze dva je pripraven na hru
        hry_prirad_do_hry(id);
        tcp_server_send_message(fd,"2|0",3);
    }
    printf(" id po startu start je %d    a fd je %d a stav: %d\n", id, fd, (GLOBAL_klienti +id)->stav_stavoveho_diagramu);
    return 0;
}


int zpracovavac_zprav_odpoved(int fd,struct s_zprava *p_zprava){
    int id = klienti_vrat_id_klienta_fd(fd);
    int odpoved=-1;
    
    if (id == -1 ){
      tcp_server_send_message(fd,"9",1);
      return -1;
    }
    printf(" pom----: %d \n", ((GLOBAL_klienti + id)->stav_stavoveho_diagramu));
    printf("pomka---- %d \n ", (GLOBAL_klienti + id)->zamek_odpovedi);
    if (((GLOBAL_klienti + id)->stav_stavoveho_diagramu ==3)&&((GLOBAL_klienti + id)->zamek_odpovedi == 0)){
        (GLOBAL_klienti + id)->zamek_odpovedi =1;
        
        
        if(p_zprava->druha_cast[0] == '1'){
            odpoved =1;
        }
        else if(p_zprava->druha_cast[0] == '2'){
            odpoved =2;
        }
        else  if(p_zprava->druha_cast[0] == '3'){
            odpoved =3;
        }
        //zde musim prevest na int
        (GLOBAL_klienti + id)->odpoved =odpoved;
        //mozna davad vedet ze odpoved prijata nebo dalsi veci
        tcp_server_send_message(fd,"3|0",3);
        (GLOBAL_klienti + id)->zamek_odpovedi =0;
    }
    else{
        tcp_server_send_message(fd,"3|1",3);
    }
    
      printf(" id po odpovedi je %d    a fd je %d a stav: %d\n", id, fd, (GLOBAL_klienti +id)->stav_stavoveho_diagramu);
    return 0;
}


int zpracovavac_zprav_odpoj(int fd,struct s_zprava *p_zprava){
  int id = klienti_vrat_id_klienta_fd(fd);
    if (id == -1){
       tcp_server_send_message(fd,"9",1); 
    }
   if (strcmp(p_zprava->druha_cast, "0")==0){
        //uplne idpojeni a zapomenuti 
        //DOPLNIT O OODSTRANENI JMENA ZE SEZNAMU
       
        printf("odebrano \n");
        if ((GLOBAL_hry + (GLOBAL_klienti +id)->herni_mistnost)->id_hrac_dva == id){
            (GLOBAL_hry + (GLOBAL_klienti +id)->herni_mistnost)->id_hrac_dva = -1; //taky tu musi bejt nejakej zamek urcite
        }
        else if ((GLOBAL_hry + (GLOBAL_klienti +id)->herni_mistnost)->id_hrac_jedna){
           (GLOBAL_hry + (GLOBAL_klienti +id)->herni_mistnost)->id_hrac_dva = -1; 
        }
        klienti_odeber_klienta(id);
        
    }
     if (strcmp(p_zprava->druha_cast, "1")==0){
         (GLOBAL_klienti + id)->stav_stavoveho_diagramu = 5;
         klienti_odhlas_klienta(id);
         tcp_server_send_message(fd,"4|0",3); 
     }
    return 0;
}



//int zpracovavat_zprav_pokud_opetovne_pripojeni()

//identifikator_sluzby|sve_id|sve_jmeno|zprava    : c|cc|zzzzzzzzzz|zzzzzzzzz......
  int zpracovavac_zprav_pokus_opetovne_pripojeni(int fd, char *msg){
  /*  printf("zacatek metody");
    char *cislo =(char*)malloc(2);
    memcpy(cislo, msg+2, 2);

    printf("cislo je: %s", cislo);
    int id = atoi(cislo);
    int pom;
    char *jmeno_hrace = malloc(10);
    memcpy(jmeno_hrace, msg+5, 10);
   
    pom = klienti_zkus_znovu_propojeni(fd, id, jmeno_hrace);
    if (pom == 0){
        tcp_server_send_message(fd, "Klient znovu pripojen, id = " + id, 0);
       
    }
    else{
        klienti_pridej_klienta(fd, jmeno_hrace);
        if (pom == -1){
            char *zprava = malloc(20);
            zprava="nezdarilo se ";
            tcp_server_send_message(fd, zprava, 1);
        }
        else{
            pom++;
            char zprava[20];
            memcpy(zprava, "efwfw", 5);
         //   zprava="Klient vytvoren.";
          //  zprava[5]='\0';
            
            tcp_server_send_message(fd, zprava, 1);
        }
             
    }
   */
}

                                                   
int zpracovavac_zprav_posli_zpet(int fd, char *msg){
    int delka = strlen(msg);
    printf("v metode prijata yprava je %s \n", msg);
    int vel = delka-15;
    char * zprava =(char*)malloc(vel);
    memcpy(zprava, msg +15, delka-15);
    tcp_server_send_message(fd, zprava, 1);
   // free(zprava);
    return 0;
}

int zpracovavac_zprav_posli_vsem(int fd, char *msg){
    int delka = strlen(msg);
    int i  ;
    int vel = delka-15;
    char * zprava2 =(char*) malloc(vel);
    memcpy(zprava2, msg +15, delka-15);
    //printf("-----------cislo------- %d \n", pocet);
    for (i=0; i<GLOBAL_pocet; i++){
        printf("posilam a i je %d", i);
        if((GLOBAL_klienti + i)->stav_stavoveho_diagramu ==5){
             tcp_server_send_message((GLOBAL_klienti + i)->fd, zprava2, 1);
        }
    }
   // free(zprava2);
    return 0;
}