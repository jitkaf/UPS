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
    int odpoved;
    int zamek_odpovedi;
    int stav_stavoveho_diagramu;
    int stav_pred_odpojenim;
    int pocet_vadnych_zprav;
}klient;


int klient_vytvor_klienta(struct klient *kli, int fd);
int klient_vynuluj_dobu_necinosti(struct klient hrac);
int klient_inkrementuj_dobu_necinosti(struct klient hrac);
int klient_prirad_herni_mistnost(struct klient hrac, int mistnost);
int klient_odeber_herni_misnost(struct klient hrac);
int klient_odpoj(struct klient hrac);
int klient_pripoj(struct klient hrac);

int klient_nastav_odpoved(struct klient hrac, int odpoved);
int klient_dej_odpoved_hrace(struct klient hrac);


#endif




