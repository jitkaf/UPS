package komunikace;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.time.LocalTime;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import data.Prostrednik;

/**
 * Stará se o posílání dat z klienta na server
 * @author jitka
 */
public class TcpOdesilac extends Thread {

    public LocalTime casOdeslani;
    Prostrednik prostrednikPos;
    private Socket socket;
    public static Scanner sc = new Scanner(System.in);
    String string = "";
    int pom;
    int delkaZpravy;
    static OutputStreamWriter wr;

    /**
     * Nastaví potřebné parametry
     * @param socket
     * @param delkaZpravy
     * @param prostrednikPos 
     */
    public TcpOdesilac(Socket socket, int delkaZpravy, Prostrednik prostrednikPos) {
        this.socket = socket;
        this.delkaZpravy = delkaZpravy;
        this.prostrednikPos = prostrednikPos;

    }

    @Override
    public void run() {
        //posilaci vlakno
        while (true) {
             if ((prostrednikPos.getZamekData() == 2)) {
                
                // if ((prostrednikPos.getCekajData() ==1)){
                System.out.println("kukajda");
                System.out.println(prostrednikPos.getZamekData());
                prostrednikPos.setZamekData(1);
                string = prostrednikPos.getData();
                System.out.println("chci poslat " + string);
                //zde bude nejaka metoda ktera transforume zpravu na spranej format		     

                pom = string.length();
                string += '\n';
                if (string.length() > 0) {
                    try {
                        wr = new OutputStreamWriter(socket.getOutputStream());
                        wr.write(string);
                        wr.flush();
                        string = "";

                    } catch (IOException e) {
                        // TODO Auto-generated catch block
                        e.printStackTrace();
                    }

                }
                prostrednikPos.setData("");
                prostrednikPos.setCekajData(0);
                prostrednikPos.setZamekData(0);

            } else {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException ex) {
                    Logger.getLogger(TcpOdesilac.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
                   }
    }

}
