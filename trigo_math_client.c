#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
	float n1;
	float res=0;
	char operator[5];
	int sock_id=socket(AF_INET,SOCK_STREAM,0);
	if(sock_id<0)
	{
		printf("Error in getting socket\n");
		return 0;
	}

	struct sockaddr_in clientstruct;
	clientstruct.sin_family=AF_INET;
	clientstruct.sin_addr.s_addr=inet_addr("127.0.0.1");
	clientstruct.sin_port=1055;

	int ret=connect(sock_id,(struct sockaddr *)&clientstruct,sizeof(clientstruct));
	if(ret==-1)
	   printf("Connection Error\n");
	else 
	   printf("Connection Accepted\n");

	printf("Enter the operator: ");
	scanf("%s",&operator);
	printf("Enter the angle: ");
	scanf("%f",&n1);
	
	printf("n1=%f,\t operator=%s,\t\n",n1,operator);
	write(sock_id,&n1,sizeof(n1));
	write(sock_id,&operator,sizeof(operator));

	int ret1=read(sock_id,&res,sizeof(res));
	printf("FROM SERVER:%f \n Bytes=%d\n",res,ret1);
	close(sock_id);

	return 0;
}
