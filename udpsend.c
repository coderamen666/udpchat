#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <time.h>

int main() {
    int sockfd;
    struct sockaddr_in dest_addr;

    char dest_ip[256];
    fprintf(stderr, "IP Address? ");
    scanf("%s", dest_ip);

    int dest_port;
    fprintf(stderr, "Port? ");
    scanf("%d", &dest_port);

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Set the destination address and port
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.s_addr = inet_addr(dest_ip);
    dest_addr.sin_port = htons(dest_port);

    char message[1028] = {0};

    while(1){

        fprintf(stderr, "? ");
        fgets(message, 1028, stdin);
        message[strlen(message) - 1] = 0;

        // Send the message
        if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1) {
            perror("sendto");
            exit(1);
        }

        bzero(message, 1028);
        time_t secs = time(0);
        struct tm *local = localtime(&secs);
        char timeString[1000];
        sprintf(timeString, "%02d:%02d:%02d", local->tm_hour, local->tm_min, local->tm_sec);
        printf("Message sent successfully at %s.\n", timeString);
    }
    // Close the socket
    close(sockfd);

    return 0;
}
