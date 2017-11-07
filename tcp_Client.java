
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
			Socket s= new Socket("localhost",6000);

			
		do
		{
			// SENDING MESSAGE TO SERVER.....

			DataOutputStream dout = new DataOutputStream (s.getOutputStream());
			System.out.println("Enter message for server...");
			userstr = sci.nextLine();
			if(userstr.equals("exit"))
			{
				break;
			}
			
			dout.writeUTF(userstr);
			
			// RECEIVING MESSAGE FROM SERVER....

			DataInputStream dis = new DataInputStream (s.getInputStream());
			str = (String)dis.readUTF(); 
			System.out.println("Message from server is:: \n"+ str);
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

