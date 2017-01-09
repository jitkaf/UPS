package komunikace;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.time.LocalTime;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import logika.ProstrednikPoslat;

public class TcpOdesilac extends Thread {

    public LocalTime casOdeslani;
    ProstrednikPoslat prostrednikPos;
    private Socket socket;
    public static Scanner sc = new Scanner(System.in);
    String string = "";
    int pom;
    int delkaZpravy;
    static OutputStreamWriter wr;

    public TcpOdesilac(Socket socket, int delkaZpravy, ProstrednikPoslat prostrednikPos) {
        this.socket = socket;
        this.delkaZpravy = delkaZpravy;
        this.prostrednikPos = prostrednikPos;

    }

    @Override
    public void run() {
        //posilaci vlakno
        System.out.println("ve vlakne " + prostrednikPos.getData());
        System.out.println("ve vlakne " + prostrednikPos.getCekajData());
        while (true) {

            // prostrednikPos.getZamekData() ; ///nechapu proc ale bez tohohle radku se nic nepolse
            if ((prostrednikPos.getZamekData() == 2)) {
                System.out.println("kuk");

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
            //     }  

            // string = string +'\n';
            //System.out.println("--");
            /*   int pom=c.getRozdil();
                        System.out.println(pom);
                         if (c.getCekaSe() == 1){
                                 if (pom > 1000){
                             
                                     System.out.println("Detekovan TIMEOUT");
                                }
                            }*/
 /*if (sc.hasNext()){
						System.out.println("-------------------------kuk");
					     string=sc.nextLine();
						
					     pom = string.length();
					     string += '\n';
						/* if(pom>delkaZpravy-1){
							 string = string.substring(0, delkaZpravy-2);
							 pom=delkaZpravy-1;
						 }
						 while(pom<delkaZpravy){
							 string=string + ' ';
							pom++;		 
						 }*/
 /*if (string.length()>0){
							try {
								wr = new OutputStreamWriter(socket.getOutputStream());
								wr.write(string);
								wr.flush();
								 string="";
                                                               // c.setCasOdeslani(LocalTime.now());
                                                             //   c.setCekaSe(1);
                                                                 
							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							
						}
					
				 }*/
        }
    }

}
