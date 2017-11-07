#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>

#define BUFLEN 512
#define PORT 8888

void die(char *s) {
    perror(s);
    exit(1);
}

int main(void) {
    struct sockaddr_in si_me, si_other;

    int sockfd, i, slen = sizeof(si_other), recv_len;
    char buf[BUFLEN];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *) &si_me, sizeof(si_me)) == -1) {
        die("bind");
    }

    while (1) {
        printf("Waiting for data...");
        fflush(stdout);

        if ((recv_len = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
            die("recvfrom()");
        }
        buf[recv_len] = '\0';

        printf("\nFile name obtained from client: %s\n", buf);
        FILE *fp = fopen(buf, "r");
        if (fp == NULL) {
            printf("Cannot open file for reading: %s\n", buf);
            buf[0] = EOF;
            if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, slen) == -1) {
                die("sendto()");
            }
            break;
        } else {
            if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, slen) == -1) {
                die("sendto()");
            }
        }
        while ((recv_len = fread(buf, 1, sizeof(buf), fp)) > 0) {
            if (sendto(sockfd, buf, recv_len, 0, (struct sockaddr *) &si_other, slen) == -1) {
                die("sendto()");
            }
        }

        fclose(fp);
        printf("File transferred.\n");

        break;
    }

    close(sockfd);
    return 0;
}