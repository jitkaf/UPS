#ifndef KLIENT_H
#define KLIENT_H

typedef
struct klient
{
    int fd;
    char* jmeno_hrace;
    int doba_necinosti;
    int herni_mistnost;
    int skore;
    int kolo;
    int pripojen;
}klient;

int metoda();
struct klient *klient_vytvor_klienta(int fd, char * jmeno_hrace);
int klient_vynuluj_dobu_necinosti(struct klient hrac);
int klient_inkrementuj_dobu_necinosti(struct klient hrac);
int klient_prirad_herni_mistnost(struct klient hrac, int mistnost);
int klient_odeber_herni_misnost(struct klient hrac);
int klient_odpoj(struct klient hrac);
int klient_pripoj(struct klient hrac);


#endif




