#ifndef KLIENTI_H
#define KLIENTI_H



int funkce() ;

int klienti_vrat_fd_klienta(struct klient* klienti, char* jmeno_hrace); //vrati fd podle jmena

int klienti_vrat_id_klienta(struct klient* klienti, char* jmeno_hrace);

struct klient* klienti_pridej_klienta(int fd, char* jmeno_hrace, struct klient* klienti);
  
struct klient* klienti_odeber_klienta(int id, struct klient* klienti);
 
int klienti_zkus_znovu_propojeni(int fd, int id, struct klient * klienti, char *jmeno_hrace);





#endif // GGG_H
