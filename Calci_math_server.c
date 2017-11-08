
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
int n1,n2,res=0;
char operator;
int session_id;
int server_id=socket(AF_INET,SOCK_STREAM,0);
if(server_id<0)
{
printf("Error in getting socket\n");
return 0;
}

struct sockaddr_in serverstruct,clientstruct;
serverstruct.sin_family=AF_INET;
serverstruct.sin_addr.s_addr=inet_addr("127.0.0.1");
serverstruct.sin_port=1050;
int i=bind(server_id,(struct sockaddr*)&serverstruct,sizeof(serverstruct));
if(i<0)
{
printf("Error in bind\n");
return 0;
}
i=listen(server_id,10);
if(i<0)
{
printf("Error in listening\n");
return 0;
}
else
 printf("Listening ...");
int client_len=sizeof(serverstruct);
while(1)
{
printf("Waiting for the client\n");
session_id=accept(server_id,(struct sockaddr*)&serverstruct,&client_len);
if(session_id==-1)
   printf("Accept Error\n");
else 
   printf("Connection Accepted\n");
read(session_id,&n1,sizeof(n1));
read(session_id,&n2,sizeof(n2));
read(session_id,&operator,sizeof(operator));

switch(operator)
{
case '+':
res=n1+n2;
break;
case '-':
res=n1-n2;
break;
case '*':
res=n1*n2;
break;
case '/':
res=n1/n2;
break;
default:
printf("invalid operation\n");
}
printf("From CLIENT:n1=%d\n",n1);
printf("From CLIENT:n2=%d\n",n2);
printf("From CLIENT:operator=%c\n",operator);
int b=write(session_id,&res,sizeof(res));
close(session_id);
}
close(server_id);
return 0;
}

