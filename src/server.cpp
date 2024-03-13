#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void parseRequest(char *buffer, int buffer_size, char *answer)
{
    char *succeded = "HTTP/1.1 200 OK\r\n\r\n";
    char *error = "HTTP/1.1 404 Not Found\r\n\r\n";
    char *sep = "\r\n";
    char *line = strtok(buffer, sep);

    if (strlen(buffer) > 4 && buffer[4] == '/')
    {
      strcpy(answer, succeded);
    }
    else
      strcpy(answer, error);
}

int main(int argc, char **argv)
{
    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cout << "Logs from your program will appear here!\n";

    // Uncomment this block to pass the first stage
    //
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        std::cerr << "Failed to create server socket\n";
        return 1;
    }

    // // Since the tester restarts your program quite often, setting REUSE_PORT
    // // ensures that we don't run into 'Address already in use' errors
    int reuse = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0)
    {
        std::cerr << "setsockopt failed\n";
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(4221);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0)
    {
        std::cerr << "Failed to bind to port 4221\n";
        return 1;
    }

    int connection_backlog = 5;
    if (listen(server_fd, connection_backlog) != 0)
    {
        std::cerr << "listen failed\n";
        return 1;
    }

    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);

    std::cout << "Waiting for a client to connect...\n";

    int clinet_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
    std::cout << "Client connected\n";

    int buffer_size = 512;
    char *buffer = (char *)calloc(buffer_size, sizeof(char));
    char *succeded = "HTTP/1.1 200 OK\r\n\r\n";
    char *error = "HTTP/1.1 404 Not Found\r\n\r\n";
    char *answer = (char *)calloc(buffer_size, sizeof(char));
    send(clinet_fd, succeded, strlen(succeded), 0);

    while (recv(clinet_fd, buffer, strlen(buffer) - 1, 0))
        ;
    {
        std::cout << buffer << std::endl;
        parseRequest(buffer, buffer_size, answer);
        send(clinet_fd, succeded, strlen(succeded), 0);
        memset(buffer, buffer_size, 0);
    }

    free(buffer);
    free(answer);
    close(server_fd);

    return 0;
}
