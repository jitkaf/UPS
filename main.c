#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
// kvuli iotctl
#include <sys/ioctl.h>
#include "konstanty.h"
#include "tcp_server.h"
#include "klient.h"
#include "klienti.h"
#include "zpracovavac_zprav.h"
#include "globalni_promenne.h"




int vyhodnotZpravu(){

}
/*Když chceš mít pole M klientů, děláš tohle
klient *pole_klientu = malloc(sizeof(klient) * M) kde M je libovolný přirozený číslo(1, 2, 3, 666, ...)
a potom když chceš získat klienta N, což je přirozený číslo v rozsahu <0; M), děláš to takhle:
klient *muj_klient = pole_klientu + N;*/
int main (void){
    int server_socket;
    int client_socket, fd;
    int return_value;
    char zprava[DELKA_ZPRAVY];
    char cbuf;
    int len_addr;
    int a2read;
    struct sockaddr_in my_addr, peer_addr;
    fd_set client_socks, tests;
    globalni_promenne_inicializace();
    char * jmeno_hrace = malloc(MAX_DELKA_JMENA);
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&my_addr, 0, sizeof(struct sockaddr_in));

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    printf("Binding port %05d ...", PORT);
    return_value = bind(server_socket, (struct sockaddr *) &my_addr, sizeof(struct sockaddr_in));
    
    if (return_value == 0)
        printf("OK\n");
    else {
        printf("ERR\n");
        return -1;
    }

    return_value = listen(server_socket, 5);
    if (return_value == 0){
        printf("Listen - OK\n");
    } else {
        printf("Listen - ER\n");
    }

    // vyprazdnime sadu deskriptoru a vlozime server socket
    FD_ZERO( &client_socks ); //- vytvori strukturu ve ktere jsou ulozeny sockety, na kterych se neco deje - vynulovanou
    FD_SET( server_socket, &client_socks ); // - nastavim serverovej socket do ty struktury
    
    int pom;
    for (;;){
        //if (fork==0){
            pom=-1;
            memset(zprava,0, DELKA_ZPRAVY);
            printf("vytvoreno %s\n",zprava);
            tests = client_socks;
            // sada deskriptoru je po kazdem volani select prepsana sadou deskriptoru kde se neco delo
            return_value = select( FD_SETSIZE, &tests, ( fd_set *)0, ( fd_set *)0, ( struct timeval *)0 );

            if (return_value < 0) {
                printf("Select - ERR\n");
                return -1;
            }
            // vynechavame stdin, stdout, stderr
            for( fd = 3; fd < FD_SETSIZE; fd++ ){
                pom++;
                // je dany socket v sade fd ze kterych lze cist ?
                if( FD_ISSET( fd, &tests ) ){
                // je to server socket ? prijmeme nove spojeni
                    if (fd == server_socket){
                        client_socket = accept(server_socket, (struct sockaddr *) &peer_addr, &len_addr); //prijme spojeni, zde muzu vytvorit strukturu pro klienta, cislo noveho klienta je v client_socket
                      
                        FD_SET( client_socket, &client_socks );
                        
                       // jmeno_hrace="nove"; //zde vytvorit nove vlakno pro nove pripojeneho
                        
                        
                        klienti_pridej_klienta(client_socket); 
                        char * zp = malloc(1);
                        zp = "a";
                        tcp_server_send_message(client_socket, zp, strlen(zp));
                        GLOBAL_pocet++;
                        printf("Pripojen novy klient (zatim neprihlasen) a pridan do sady socketu\n");
                    }
                    // je to klientsky socket ? prijmem data
                    else {
                        // pocet bajtu co je pripraveno ke cteni
                        ioctl( fd, FIONREAD, &a2read );
                        // mame co cist
                        if (a2read > 0){
                           read(fd,zprava , a2read);
                            printf("Prijato %s od klienta  -- %d --\n",zprava, fd);
                            zpracovavac_zprav_vyhodnot_zpravu(fd, zprava, a2read);
                           // tcp_server_send_message(fd,zprava,a2read );
                        }
                        // na socketu se stalo neco spatneho
                        else {
                            close(fd);
                            FD_CLR( fd, &client_socks );
                            int id =klienti_vrat_id_klienta_fd(fd);
                            if ((GLOBAL_klienti + id )->stav_stavoveho_diagramu == 0){ //pokud je neregistrovanej uplne ho zahodim
                                klienti_odeber_klienta(id);
                                printf("Klient se odpojil a byl odebran ze sady socketu- uplne vymazan\n");
                            }else{
                               klienti_odhlas_klienta(id); //pokud uz je zaregistrovanej zustane tu v pameti
                               printf("Klient se odpojil a byl odebran ze sady socketu - zustal v pameti jako odhlaseny \n");
                            }
                            printf("Klient se odpojil a byl odebran ze sady socketu\n");
                        }
                    }
                }
            }   
    }

    return 0;
}



