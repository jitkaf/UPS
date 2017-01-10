package komunikace;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.time.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import logika.ProstrednikPoslat;
import uzivatelskeRozhrani.IPohled;

public class TcpPrijmac extends Thread {

    public LocalTime aktualni, odeslano;
    Socket socket;
    static BufferedReader bfr;
    ProstrednikPoslat prostrednikPos;

    public TcpPrijmac(Socket socket, int bufferSize, ProstrednikPoslat prostrednikPos) {
        this.socket = socket;
        this.prostrednikPos = prostrednikPos;
        System.out.println("ted");
    }

    @Override
    public void run() {
        System.out.println("jedu");
        while (true) {
            System.out.println("druhe");

            // System.out.println("cekamNaZpracvu");
            try {
                bfr = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String message = bfr.readLine();
                if (message == null) {
                    System.err.println("Stream byl ukončen.");
                    break;
                }
                if (message.length() > 0) {

                    System.out.println("Message Received: " + message);
                    zpracujZpravu(message);
                }
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        }
    }

    public int zpracujZpravu(String zprava) {
        String[] casti = zprava.split("|");
        int delka = casti.length;
        System.out.println("budu zpracovavat zpravy: " + delka);
        if (casti[0].length() < 1) {
            return -1;
        } 
        else if (casti[0].charAt(0) == '0') {
            if (delka > 2) {
                vyhodnoceniPrihlaseni(casti[2]);
            }
        }
        else if(casti[0].charAt(0)=='1'){
            //znovupripojeni
        }
        else if(casti[0].charAt(0)== '2'){
            //prejde na cekani na otazku
           this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_CEKANI);
        }
        else if(casti[0].charAt(0) == '8'){
            if (delka >8){
                zpracujOtazku(casti[2], casti[4], casti[6], casti[8]);
            }
        }
        return 0;
    }

    public int vyhodnoceniPrihlaseni(String s) {
        System.out.println("jsem vy vyhodnot: " + s  +   " : "+ s.charAt(0));
        if ((s.length() < 1)/* || (prostrednikPos.getStavStavovehoDiagramu() != 0)*/) { //zde taky osetrovat ze je neprihlasen jeste
            return -1;
        }
        if (s.charAt(0) == '0') {
            System.out.println("prislo ze registrace je ok");
            /*while (prostrednikPos.getZamekData() != 0) {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException ex) {
                    Logger.getLogger(TcpPrijmac.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
            prostrednikPos.setZamekData(1);
            prostrednikPos.setData("1");
            prostrednikPos.setZamekData(3);*/

            this.prostrednikPos.getPohled().prepniSe(IPohled.START);
        } else if (s.charAt(0) == '3') {
            System.out.println("prislo ze registrace neni ok - dusplicidni jmenok");
            this.prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI_CHYBA);
          /*  prostrednikPos.setZamekData(1);
            prostrednikPos.setData("0");
            prostrednikPos.setZamekData(3);*/
        }
        else{
            System.out.println("prislo neplatne potvrzeni prihlaseni");
        }
        return 0;
    }
    
    
    public void zpracujOtazku(String otazka, String a, String b, String c){
        //asi budu muset pouzit nejake zamky nebezpecne je to takhle
        this.prostrednikPos.setOtazka(otazka);
        this.prostrednikPos.setAcko(a);
        this.prostrednikPos.setBecko(b);
        this.prostrednikPos.setCecko(c);
        this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_OTAZKA);
    }

}
