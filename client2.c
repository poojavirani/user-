#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h>

#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 8888

void die(char *s) {
    perror(s);
    exit(1);
}

int main(void) {
    struct sockaddr_in si_other;
    int sockfd, i, slen = sizeof(si_other), recv_len;
    char buf[BUFLEN];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER, &si_other.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    while (1) {

        bzero(buf, sizeof(buf));
        printf("\nEnter file name: ");
        fgets(buf, sizeof(buf), stdin);
        i = 0;
        while (buf[i++] != '\n');
        buf[i - 1] = '\0';
        printf("\nFile name: %s\n", buf);
        if (sendto(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &si_other, slen) == -1) {
            die("sendto()");
        }
        bzero(buf, sizeof(buf));
        recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen);
        if (buf[0] == EOF) {
            printf("File not found on server!\n");
            break;
        }
        FILE *fp = fopen(buf, "w");
        if (fp == NULL) {
            printf("File %s cannot be opened for writing.\n", buf);
            exit(1);
        }
        while ((recv_len = recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) != -1) {
            fwrite(buf, 1, recv_len, fp);
            fflush(fp);
            if (recv_len < BUFLEN)
                break;
        }
        fclose(fp);
        printf("File transferred.\n");
        break;
    }

    close(sockfd);
    return 0;
}