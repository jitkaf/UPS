import java.io.*;
import java.net.*;
import java.util.Scanner;

import TCP.TcpOdesilac;
import TCP.TcpPrijmac;

class ClientTCP extends Thread
{
	
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
 public static void main(String argv[]) throws Exception
 {
	socket = new Socket("127.0.0.1", 20001);
	adresa = socket.getInetAddress();
	System.out.print("Pripojuju se na : "+adresa.getHostAddress()+" se jmenem : "+adresa.getHostName()+"\n" );

  
//  StringOutputStrema ssss = new StringOutputSStream;
  //ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
  //oos.writeObject(string);
  
  
  
  //System.out.println("Odeslano " + string );
 // wr.flush(); //bez tohohle se neposle nic
  //ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
  //String message = (String) ois.readObject();
  
 //
	 
	 // string="nic";
	// pom = string.length();
	 //cteci vlakno
	 TcpPrijmac t2 = new TcpPrijmac(socket, delkaZpravy);
	 TcpOdesilac t1 = new TcpOdesilac(socket, delkaZpravy);
    
		 t1.start();
		 t2.start();
		 
		 if (vypsano == 0){
			 vypsano =1;
			 System.out.print("Zadejte zpravu(max 250 znaků): ");
		 }
		 
		 t1.join();
		 t2.join();
  
 
  //bfr.close();
 // wr.close();
 // socket.close();
  
 }
}
