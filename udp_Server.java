
import java.net.*;
import java.io.*;
import java.util.*;

public class Server
{

	public static void main(String[] args) 
	{
		Scanner sci = new Scanner(System.in);
		String userstr ,str;	
		int ch=1;	
		try
		{
			DatagramSocket ds;

			do
			{

				// RECEIVING MESSAGE FROM CLIENT......

				ds = new DatagramSocket(8080);
				byte[] buf = new byte[1024];
				DatagramPacket dp1 = new DatagramPacket (buf,1024);
				ds.receive(dp1);
				str = new String(dp1.getData(),0,dp1.getLength());

				if(str.equals("exit"))
				{
					break;
				}
				ds.close();
				System.out.println("Message from client is:: \n"+ str);

				// SENDING MESSAGE TO CLIENT.... 

				ds = new DatagramSocket();
				System.out.println("Enter message for client...");
				userstr = sci.nextLine();

				
				InetAddress in = InetAddress.getByName("localhost");
				DatagramPacket dp2 = new DatagramPacket (userstr.getBytes(),userstr.length(),in,8082);
				ds.send(dp2);
				if(userstr.equals("exit"))
				{
					break;
				}

				ds.close();
			}while(ch==1);

			// CLOSING CONNECTIONS.....
			
			System.out.println("EXITED......");
			ds.close();
			
		}
		catch (Exception e)
		{
			System.out.println("EXITED......");
		}

	}

}

