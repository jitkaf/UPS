#ifndef KLIENT_H
#define KLIENT_H

typedef
struct klient
{
    int fd;
    char* jmeno_hrace;
    char *heslo;
    int doba_necinosti;
    int herni_mistnost;
    int skore;
    int kolo;
    int odpoved;
    int zamek_odpovedi;
    int stav_stavoveho_diagramu;
}klient;

int metoda();
struct klient *klient_vytvor_klienta(int fd);

int klient_vynuluj_dobu_necinosti(struct klient hrac);
int klient_inkrementuj_dobu_necinosti(struct klient hrac);
int klient_prirad_herni_mistnost(struct klient hrac, int mistnost);
int klient_odeber_herni_misnost(struct klient hrac);
int klient_odpoj(struct klient hrac);
int klient_pripoj(struct klient hrac);
int klient_generuj_heslo();
int klient_nastav_odpoved(struct klient hrac, int odpoved);
int klient_dej_odpoved_hrace(struct klient hrac);


#endif




