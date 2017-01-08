

import java.io.*;
import java.net.*;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;


import komunikace.TcpOdesilac;
import komunikace.TcpPrijmac;
import logika.ProstrednikPoslat;
import uzivatelskeRozhrani.Okno;
import uzivatelskeRozhrani.Spravce;
//import uzivatelskeRozhrani.Okno;



/**
 * Hlavní třída aplikace, vytvoří GUI.
 * @author Jitka Furbacherová
 *
 */
public class NewFXMain  extends Thread{

        
        //ups
      
    	  static String sentence;
	  static String modifiedSentence;
	  static Socket socket;
	  static InetAddress adresa;
	  static int delkaZpravy=255;
	 
	 static OutputStreamWriter wr;
	  static int pom =3;
	  static int zamek=0;
	  static int vypsano=0;
	  static int stridani=0;
	
	/**
	 * Main aplikce
	 * @param args
	 */
	public static void main(String[] args){
                  try {
                      socket = new Socket("127.0.0.1", 20001);
                      adresa = socket.getInetAddress();
                      System.out.print("Pripojuju se na : "+adresa.getHostAddress()+" se jmenem : "+adresa.getHostName()+"\n" );
                  } catch (IOException ex) {
                      System.out.println("Pripojeni selhalo, program byl ukoncen.");
                      return;
                  }
            	

            ProstrednikPoslat prostrednikPos = new ProstrednikPoslat();
            TcpPrijmac t2 = new TcpPrijmac(socket, delkaZpravy);
            TcpOdesilac t1 = new TcpOdesilac(socket, delkaZpravy, prostrednikPos);
            Spravce t3 = new Spravce(prostrednikPos);

            t1.start();
            t2.start();
            t3.start();

            if (vypsano == 0){
                vypsano =1;
                System.out.print("Zadejte zpravu(max 250 znaků): ");
            }
	
      
                 
	
                  try {
                      t1.join();
                      t2.join();
                      t3.join();
                  } catch (InterruptedException ex) {
                      Logger.getLogger(NewFXMain.class.getName()).log(Level.SEVERE, null, ex);
                  }
   
                
    }
	
}
