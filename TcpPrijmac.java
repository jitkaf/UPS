package TCP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class TcpPrijmac extends Thread{
	
	Socket socket;
	static BufferedReader bfr;
	
	public TcpPrijmac(Socket socket, int bufferSize){
		this.socket = socket;
	}
	
	
	@Override
	 public void run(){
		 while(true){
			// System.out.println("druhe");
			System.out.println("**********************************");
			 
			  try {
				bfr = new BufferedReader(new InputStreamReader(socket.getInputStream()));
				 String message = bfr.readLine();
				 if (message == null){
					 System.err.println("Stream byl ukončen.");
					 break;
				 }
				 if (message.length() >0){
					  System.out.println("Message Received: "  + message); 
				  }
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		 }
	 }
}
