#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>

#define BUFFER_SIZE 1024 // Size of the receive buffer

int main() {
    int sockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_len = sizeof(cli_addr);
    char buffer[BUFFER_SIZE];
    int bytes_received;

    int port;
    fprintf(stderr, "Port? ");
    scanf("%d", &port);

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Bind the socket to the port
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    printf("Listening on port %d...\n", port);

    // Receive packets
    while (1) {
        bzero(buffer, BUFFER_SIZE);
        bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cli_addr, &cli_addr_len);
        if (bytes_received == -1) {
            perror("recvfrom");
            exit(1);
        }
        time_t secs = time(0);
        struct tm *local = localtime(&secs);
        char timeString[1000];
        sprintf(timeString, "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
        printf("Received %d bytes from %s:%d at %s: %s\n", bytes_received, inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port), timeString, buffer);
    }

    // Close the socket
    close(sockfd);

    return 0;
}
