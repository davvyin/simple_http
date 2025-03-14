// A simple server in c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define DOMAIN AF_INET
#define USE_PORT 8080
#define BUFFER_SIZE 1024

int main()
{
        struct sockaddr_in address;
        int server_fd = socket(DOMAIN, SOCK_STREAM, 0);
        socklen_t addrlen = sizeof(address);

        int socket_fd;
        if (server_fd < 0)
        {
                perror("socket failed");
                exit(EXIT_FAILURE);
        }
        // set the address specs
        address.sin_family = DOMAIN;
        address.sin_port = htons(USE_PORT);
        address.sin_addr.s_addr = INADDR_ANY;
        // bind the socket to the address struct
        if (bind(server_fd, (struct sockaddr *)&address,
                 sizeof(address)) < 0)
        {
                perror("bind failed");
                exit(EXIT_FAILURE);
        }
        // start the listening for the clients
        // max 3 backlogs
        if (listen(server_fd, 3) < 0)
        {
                perror("listen");
                exit(EXIT_FAILURE);
        }

        while (1)
        {
                // start connection
                if ((socket_fd = accept(server_fd, (struct sockaddr *)&address,
                                        &addrlen)) < 0)
                {
                        perror("accept");
                        exit(EXIT_FAILURE);
                }
                ssize_t valread;
                char *buffer = malloc(BUFFER_SIZE);
                char *hello = "Hello from server";

                valread = read(socket_fd, buffer, BUFFER_SIZE - 1);
                printf("Buffer %s\n", buffer);
                send(socket_fd, hello, strlen(hello), 0);
                printf("Message sent \n");
        }

        // close socket and the server
        close(socket_fd);
        close(server_fd);
        return 0;
}