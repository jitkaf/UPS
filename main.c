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


int main(int argc, char **argv) {
    printf("Byl spuštěn server\n");
    int port=-1;
    if (argc >2 ){
        if (strcmp(argv[2], "-h")==0){
            printf("Program spusťe příkazem \".\\server port\" kde \"port je číslo od 1024 do 65535\". Pokud nezadáte port, bude použita defaultní hodnota \"20001\". ");
        }
        else {
            port = atoi(argv[2]);
            if ((port == NULL ) || (port<1024) || (port >35535)){
                printf("Zadán nesmyslný port. Port musí být zadán číselně v rozsahu 1024-65535");
                return -1;
            }
        }
    }
    herni_otazky_nacti_otazky();
   
    int server_socket;
    int client_socket, fd;
    int return_value;
    char zprava[MAX_DELKA_ZPRAVY_KLIENT];
    int len_addr;
    int a2read;
    struct sockaddr_in my_addr, peer_addr;
    fd_set client_socks, tests;
    globalni_promenne_inicializace();
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&my_addr, 0, sizeof (struct sockaddr_in));
    if (port == -1){
        port = PORT;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    
    printf("Binding port %05d ...", port);
    return_value = bind(server_socket, (struct sockaddr *) &my_addr, sizeof (struct sockaddr_in));

    if (return_value == 0)
        printf("OK\n");
    else {
        printf("ERR Zkuste zadat jiný port. \n");
        return -1;
    }

    return_value = listen(server_socket, 5);
    if (return_value == 0) {
        printf("Listen - OK\n");
    } else {
        printf("Listen - ER\n");
    }

    // vyprazdnime sadu deskriptoru a vlozime server socket
    FD_ZERO(&client_socks); //- vytvori strukturu ve ktere jsou ulozeny sockety, na kterych se neco deje - vynulovanou
    FD_SET(server_socket, &client_socks); // - nastavim serverovej socket do ty struktury

    int pom;
    for (;;) {
        pom = -1;
        memset(zprava, 0, MAX_DELKA_ZPRAVY_KLIENT);
       
        tests = client_socks;
        // sada deskriptoru je po kazdem volani select prepsana sadou deskriptoru kde se neco delo
        return_value = select(FD_SETSIZE, &tests, (fd_set *) 0, (fd_set *) 0, (struct timeval *) 0);

        if (return_value < 0) {
            printf("Select - ERR\n");
            return -1;
        }
        // vynechavame stdin, stdout, stderr
        for (fd = 3; fd < FD_SETSIZE; fd++) {
            pom++;
            // je dany socket v sade fd ze kterych lze cist ?
            if (FD_ISSET(fd, &tests)) {
                // je to server socket ? prijmeme nove spojeni
                if (fd == server_socket) {
                    client_socket = accept(server_socket, (struct sockaddr *) &peer_addr, &len_addr); //prijme spojeni, zde muzu vytvorit strukturu pro klienta, cislo noveho klienta je v client_socket
                    FD_SET(client_socket, &client_socks);
                    klienti_pridej_klienta(client_socket);
                    char * zp = malloc(1);
                    zp = "6|0";
                    tcp_server_send_message(client_socket, zp);

                    printf("Pripojen nový klient (zatím nepřihlášen) a přidán do sady socketů\n");  
                }                    // je to klientsky socket ? prijmem data
                else {
                    // pocet bajtu co je pripraveno ke cteni
                    ioctl(fd, FIONREAD, &a2read);
                    // mame co cistm
                    if (a2read>MAX_DELKA_ZPRAVY_KLIENT){
                         int id = klienti_vrat_id_klienta_fd(fd);
                         klienti_odeber_klienta(id, fd, &client_socks);
                         printf("Klient odpojen za nevhodné chování.\n ");
                    }
                     else if (a2read > 0) {
                        read(fd, zprava, a2read);
                        printf("Prřijato %s od klienta  -- %d --\n", zprava, fd);
                        zpracovavac_zprav_vyhodnot_zpravu(fd, zprava, a2read, &client_socks);
                        // tcp_server_send_message(fd,zprava,a2read );
                    }                        // na socketu se stalo neco spatneho
                    else {
                        /* close(fd);
                         FD_CLR( fd, &client_socks );*/
                        int id = klienti_vrat_id_klienta_fd(fd);
                        if (((GLOBAL_klienti + id)->stav_stavoveho_diagramu != 2) && ((GLOBAL_klienti + id)->stav_stavoveho_diagramu != 3)) { //pokud je neregistrovanej uplne ho zahodim
                            klienti_odeber_klienta(id, fd, &client_socks);
                            printf("Klient se odpojil a byl odebrán ze sady socketů - uplně vymazán\n");
                        } else {
                            klienti_odhlas_klienta(id, fd, &client_socks); //pokud uz je zaregistrovanej zustane tu v pameti
                            printf("Klient se odpojil a byl odebran ze sady socketu - zustal v pameti jako odhlaseny \n");
                        }
                        printf("Klient se odpojil a byl odebran ze sady socketu\n");
                    }
                    printf("\n ----  %s    %d \n", (GLOBAL_klienti + GLOBAL_pocet - 1)->jmeno_hrace, (GLOBAL_pocet));
                }
            }
        }
    }

    return 0;
}