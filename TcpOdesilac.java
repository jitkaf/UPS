package TCP;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.Scanner;

public class TcpOdesilac extends Thread {

	private Socket socket;
	public static Scanner sc = new Scanner (System.in);
	String string="";
	int pom;
	int delkaZpravy;
	static OutputStreamWriter wr;
	
	public TcpOdesilac(Socket socket, int delkaZpravy){
		this.socket = socket;
		this.delkaZpravy = delkaZpravy;
	}
	
	@Override
	 public void run(){
		//posilaci vlakno
		 while(true){
			// string = string +'\n';
		
			//System.out.println("--");
					if (sc.hasNext()){
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
						if (string.length()>0){
							try {
								wr = new OutputStreamWriter(socket.getOutputStream());
								wr.write(string);
								wr.flush();
								 string="";
							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
							
						}
					
				 }
				
		
			
			
		 }
	 }
}
