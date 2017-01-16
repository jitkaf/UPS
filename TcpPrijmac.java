package komunikace;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.time.*;
import data.Prostrednik;
import uzivatelskeRozhrani.IPohled;

/**
 * Stará se o přijímání zpráv od serveru a následné rozparsování.
 * @author jitka
 */
public class TcpPrijmac extends Thread {

    public LocalTime aktualni, odeslano;
    Socket socket;
    static BufferedReader bfr;
    Prostrednik prostrednikPos;

    /**
     * Nastaví potřebné parametry.
     * @param socket
     * @param bufferSize
     * @param prostrednikPos 
     */
    public TcpPrijmac(Socket socket, int bufferSize, Prostrednik prostrednikPos) {
        this.socket = socket;
        this.prostrednikPos = prostrednikPos;
     }

    @Override
    public void run() {
        while (true) {
           try {
                bfr = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                String message = bfr.readLine();
                if (message == null) {
                    System.err.println("Stream byl ukončen.");
                    System.exit(0);
                    break;
                }
                if (message.length() > 0) {
                    System.out.println("Obdržena zpráva: " + message);
                    zpracujZpravu(message);
                }
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        }
    }

    public int zpracujZpravu(String zprava) {
        String[] casti = zprava.split("\\|");
        int delka = casti.length;
        if (casti[0].length() < 1) {
            return -1;
        } 
        else if (casti[0].charAt(0) == '0') {
            if (delka > 1) {
                vyhodnoceniPrihlaseni(casti[1]);
            }
        }
        else if(casti[0].charAt(0)=='1'){
            if (delka > 1) {
            vyhodnotZnovuPripojeni(casti[1]);
            }
        }
        else if(casti[0].charAt(0)== '2'){
            //prejde na cekani na otazku
            System.out.println("prijata dvojka cekani na zacatek hry");
           this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_CEKANI);
        }
        else if(casti[0].charAt(0) == '5'){
            if (delka>1){
                zpracujVysledky(casti[1]);
            }
        }
        else if(casti[0].charAt(0) == '8'){
            if (delka >4){
                zpracujOtazku(casti[1], casti[2], casti[3], casti[4]);
            }
        }
        else if (casti[0].charAt(0) == '9'){
            System.out.println("Chyba");
        }
        else if(casti[0].charAt(0) == '6'){
            //prihlasei ok
        }
        else {
            System.err.println("Detekovano pochybne chovani serveru. Aplikace bude ukončena");
            System.exit(0);
                    
        }
        return 0;
    }

    /**
     * Zpracuje odpověď serveru na pokus o přihlášení.
     * @param s
     * @return 
     */
    public int vyhodnoceniPrihlaseni(String s) {
        System.out.println("jsem vy vyhodnot: " + s  +   " : "+ s.charAt(0));
        if ((s.length() < 1)/* || (prostrednikPos.getStavStavovehoDiagramu() != 0)*/) { //zde taky osetrovat ze je neprihlasen jeste
            return -1;
        }
        if (s.charAt(0) == '0') {
            System.out.println("prislo ze registrace je ok");
           
            this.prostrednikPos.getPohled().prepniSe(IPohled.START);
        
        }else if(s.charAt(0) == '1'){
            this.prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI_JMENO);
        }else if(s.charAt(0) == '2'){
            this.prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI_HESLO);
        }else if (s.charAt(0) == '3') {
            System.out.println("prislo ze registrace neni ok - duplicidni jmeno");
            this.prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI_DUPLICITA);
        }
        else{
            System.out.println("prislo neplatne potvrzeni prihlaseni");
        }
        return 0;
    }
    
    /**
     * Vyhodnoti znovu pripojeni
     * @param s
     * @return 
     */
    public int vyhodnotZnovuPripojeni(String s) {
        System.out.println("jsem vy vyhodnot: " + s  +   " : "+ s.charAt(0));
        if ((s.length() < 1)/* || (prostrednikPos.getStavStavovehoDiagramu() != 0)*/) { //zde taky osetrovat ze je neprihlasen jeste
            return -1;
        }
        if (s.charAt(0) == '0') {
        System.out.println("prislo ze prihlasenije ok");
           
        this.prostrednikPos.getPohled().prepniSe(IPohled.START);
        
        }else if(s.charAt(0) == '1'){
            this.prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI_JMENO);
        }else if(s.charAt(0) == '2'){
            this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_CEKANI);
        }else if(s.charAt(0) == '3'){
            this.prostrednikPos.getPohled().prepniSe(IPohled.PRIHLASENI_DUPLICITA);
        }else{
            System.out.println("prislo neplatne potvrzeni prihlaseni");
        }
        return 0;
    }
    
    
    /**
     * Zpracuju otázku
     * @param otazka
     * @param a
     * @param b
     * @param c 
     */
    public void zpracujOtazku(String otazka, String a, String b, String c){
        //asi budu muset pouzit nejake zamky nebezpecne je to takhle
        System.out.println("prijata otazka");
        this.prostrednikPos.setOtazka(otazka);
        this.prostrednikPos.setAcko(a);
        this.prostrednikPos.setBecko(b);
        this.prostrednikPos.setCecko(c);
        this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_OTAZKA);
    }
    
    /**
     * Zpracuje výsledky
     * @param vysledek 
     */
    private void zpracujVysledky(String vysledek){
        System.out.println("Zpracuj vysledky " + vysledek);
        if(vysledek.charAt(0) == '0'){
            this.prostrednikPos.setVysledek(0);
            this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_VYHODNOCENI);
        }
        else if(vysledek.charAt(0) == '1'){
            this.prostrednikPos.setVysledek(1);
            this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_VYHODNOCENI);
        }
        else if(vysledek.charAt(0) == '2'){
            this.prostrednikPos.setVysledek(2);
            this.prostrednikPos.getPohled().prepniSe(IPohled.HRA_VYHODNOCENI);
        }
    }

}
