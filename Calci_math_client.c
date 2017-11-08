#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
	int n1,n2,ch;
	int res=0;
	char operator;
	int sock_id=socket(AF_INET,SOCK_STREAM,0);
	if(sock_id<0)
	{
	printf("Error in getting socket\n");
	return 0;
	}

	struct sockaddr_in clientstruct;
	clientstruct.sin_family=AF_INET;
	clientstruct.sin_addr.s_addr=inet_addr("127.0.0.1");
	clientstruct.sin_port=1050;

	int ret=connect(sock_id,(struct sockaddr *)&clientstruct,sizeof(clientstruct));
	if(ret==-1)
	   printf("Connection Error\n");
	else 
	   printf("Connection Accepted\n");

	printf("Enter the operation you wanna perform: \n1. Addition\n2. Subtraction\n3. Multiplication\n4. Division");
	scanf("%d",&ch);
	switch(ch)
	{
	case 1:
		operator='+';
		break;
	case 2:
		operator='-';
		break;
	case 3:
		operator='*';
		break;
	case 4:
		operator='/';
		break;
	}
	printf("\nEnter the first operand: ");
	scanf("%d",&n1);
	printf("\nEnter the second operand: ");
	scanf("%d",&n2);
	printf("n1=%d,\t operator=%c,\t, n2=%d\n",n1,operator,n2);
	write(sock_id,&n1,sizeof(n1));
	write(sock_id,&n2,sizeof(n2));
	write(sock_id,&operator,sizeof(operator));

	int ret1=read(sock_id,&res,sizeof(res));
	printf("FROM SERVER:%d \n Bytes=%d\n",res,ret1);
	close(sock_id);
	return 0;
}
