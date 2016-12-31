#ifndef KLIENTI_H
#define KLIENTI_H



int funkce() ;
int klienti_zaregiastruj_klienta(int id, char *jmeno, char *heslo);

int klienti_znovu_prihlaseni(int fd, char *jmeno, char *heslo);

int klienti_vrat_fd_klienta( char* jmeno_hrace); //vrati fd podle jmena

int klienti_vrat_id_klienta (char* jmeno_hrace);

int klienti_vrat_id_klienta_fd(int fd);

int klienti_pridej_klienta(int fd);

int klienti_odhlas_klienta(int id);
  
int klienti_odeber_klienta(int id);
 
int klienti_zkus_znovu_propojeni(int fd, int id, char *jmeno_hrace);





#endif // GGG_H
