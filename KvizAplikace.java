
import java.io.*;
import java.net.*;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import komunikace.TcpOdesilac;
import komunikace.TcpPrijmac;
import logika.ProstrednikPoslat;
import uzivatelskeRozhrani.IPohled;
import uzivatelskeRozhrani.KvizScena;
import uzivatelskeRozhrani.StavitelObsahuOkna;

//import uzivatelskeRozhrani.Okno;
/**
 * Hlavní třída aplikace, vytvoří GUI.
 *
 * @author Jitka Furbacherová
 *
 */
public class KvizAplikace extends Application {

    //ups
    ProstrednikPoslat prostrednikPos;
    String sentence;
    String modifiedSentence;
    Socket socket;
    int delkaZpravy = 255;

    OutputStreamWriter wr;
    int pom = 3;
    int zamek = 0;
    int vypsano = 0;
    int stridani = 0;

    @Override
    public void start(Stage s) throws Exception {
        
        try {
            socket = new Socket("127.0.0.1", 20001);
            System.out.print("Pripojeno na : " + socket.getInetAddress().toString());
        } catch (IOException ex) {
            System.err.println("Pripojeni selhalo, program byl ukoncen.");
            return;
        }
        
        
        prostrednikPos = new ProstrednikPoslat();
        prostrednikPos.setData("lalala jsem dato");
        System.out.println("ve start " + prostrednikPos.getData());

        KvizScena kvizScena = new KvizScena(prostrednikPos);
        prostrednikPos.setPohled(kvizScena);
        kvizScena.prepniSe(IPohled.PRIHLASENI);
        
        
        
        
        s.setTitle("Vědomostní kvíz");
        s.setScene(kvizScena);
        //s.setScene(new Scene(new AnchorPane(new Button("Ahoj"))));
        s.setMinHeight(750);
        s.setMinWidth(700);
        s.setMaxHeight(800);
        s.setMaxWidth(750);
        s.setY(100);
        s.show();
        
        
        prostrednikPos.tcpOdesilac = new TcpOdesilac(socket, delkaZpravy, prostrednikPos);
        prostrednikPos.tcpPrijimac = new TcpPrijmac(socket, delkaZpravy, prostrednikPos);
        
        //Okno.launch(Okno.class);
        prostrednikPos.tcpOdesilac.start();
        prostrednikPos.tcpPrijimac.start();
        // t3.start();
        /**
        try {
            prostrednikPos.tcpOdesilac.join();
            prostrednikPos.tcpPrijimac.join();
            // t3.join();
        } catch (InterruptedException ex) {
            Logger.getLogger(KvizAplikace.class.getName()).log(Level.SEVERE, null, ex);
        }
        */
    }

    /**
     * Main aplikce
     *
     * @param args
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
