
import java.net.*;
import java.io.*;
import java.util.*;



public class Client
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
			
				// SENDING MESSAGE TO SERVER.....

				ds = new DatagramSocket();
				System.out.println("Enter message for server...");
				userstr = sci.nextLine();

				InetAddress in = InetAddress.getByName("localhost");
				DatagramPacket dp1 = new DatagramPacket (userstr.getBytes(),userstr.length(),in,8080);
				ds.send(dp1);


				if(userstr.equals("exit"))
				{
					break;
				}

				ds.close();


				// RECEIVING MESSAGE FROM SERVER....

				ds = new DatagramSocket(8082);
				byte[] buf = new byte[1024];
				DatagramPacket dp2 = new DatagramPacket (buf,1024);
				ds.receive(dp2);
				str = new String(dp2.getData(),0,dp2.getLength());

				if(str.equals("exit"))
				{
					break;
				}

				System.out.println("Message from server is:: \n"+ str);
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

