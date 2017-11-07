import java.net.*;
import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class Server 
{
	int port;
	ServerSocket sc = null;
	Socket s = null;
	ExecutorService pool = null;
	
	public Server(int port)
	{
		this.port = port;
		pool = Executors.newFixedThreadPool(5);
	}
	
	public void startServer()
	{
		try 
		{
			//creating one server socket 
			sc = new ServerSocket(6000);
			//for accepting multiple clients
			while(true)
			{
				System.out.println("Server waiting for client....");
				s = sc.accept();
				
				System.out.println("Got one client.Creating thread for this client...");
				ServerThreadBody runnable = new ServerThreadBody(s, this);
				//assigning thread to pool
				pool.execute(runnable);
			}
			
		} catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) 
	{
		new Server(6000).startServer();
	}
	
}

class ServerThreadBody implements Runnable
{
	Server server = null;
	Socket s = null;
	ServerThreadBody(Socket s, Server server) 
	{
		this.s = s;
		this.server = server;
	}
		public void run()
	{
		Scanner sci = new Scanner(System.in);
		String userstr ,str;
		int ch=1;
		try
		{
			do
			{
				
				// RECEIVING MESSAGE FROM CLIENT......

				DataInputStream dis = new DataInputStream (s.getInputStream());
				str = (String)dis.readUTF(); 
				System.out.println("Message from client is:: \n"+ str);

				// SENDING MESSAGE TO CLIENT.... 

				DataOutputStream dout = new DataOutputStream (s.getOutputStream());
				System.out.println("Enter message for client...");
				userstr = sci.nextLine();
				if(userstr.equals("exit"))
				{
					break;
				}
				
				dout.writeUTF(userstr);
			}while(ch==1);

				// CLOSING CONNECTIONS.....
				
				System.out.println("EXITED......");
				s.close();
		}
		catch (Exception e)
		{
			System.out.println("EXITED......");
		}

	}

}

