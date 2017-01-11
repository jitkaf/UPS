
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
   


    @Override
    public void start(Stage s) throws Exception {
        
        
        
        prostrednikPos = new ProstrednikPoslat();
        prostrednikPos.setData("lalala jsem dato");
        System.out.println("ve start " + prostrednikPos.getData());

        KvizScena kvizScena = new KvizScena(prostrednikPos);
        prostrednikPos.setPohled(kvizScena);
        System.out.println("ipohled ze start " + IPohled.PRIHLASENI);
        kvizScena.prepniSe(IPohled.PRIPOJENI);
        
        
        
        
        s.setTitle("Vědomostní kvíz");
        s.setScene(kvizScena);
        //s.setScene(new Scene(new AnchorPane(new Button("Ahoj"))));
        s.setMinHeight(500);
        s.setMinWidth(500);
        s.setMaxHeight(600);
        s.setMaxWidth(550);
        s.setY(100);
        s.show();
        
        
        
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
