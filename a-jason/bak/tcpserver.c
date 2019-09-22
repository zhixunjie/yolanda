//netstat -ltnp
//telnet 127.0.0.1 12345
#include <stdio.h>
#include <lib/common.h>

void read_data(int sockfd) {
    ssize_t n;
    char buf[1024];

    int time = 0;
    for (;;) {
        fprintf(stdout, "block in read\n");
        if ((n = readn(sockfd, buf, 1024)) == 0)
            return;

        time++;
        fprintf(stdout, "1K read for %d \n", time);
        usleep(1000);
    }
}


int main() {

    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);

    bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    int backlog = 1024;
    listen(listenfd, backlog);

    while (1) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockadd *) &cliaddr, &clilen);
        read_data(connfd);
        close(connfd);
    }

    return 0;
}