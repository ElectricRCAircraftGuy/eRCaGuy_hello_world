/*
GS
May 2025

epoll_server

Prompt to Grok: 
> Write a simple and complete single file epoll demo in C++

https://grok.com/share/bGVnYWN5_9a3eabbe-cf6c-4c30-8c53-97a36740c086

[ ] study and clean up this file to ensure I understand it all

*/

#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAX_EVENTS 10
#define BUFFER_SIZE 1024
#define PORT 8080

void set_non_blocking(int sockfd) {
    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    // Create server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        return 1;
    }

    // Set socket to non-blocking
    set_non_blocking(server_fd);

    // Set socket options
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind socket
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        close(server_fd);
        return 1;
    }

    // Listen
    if (listen(server_fd, SOMAXCONN) < 0) {
        std::cerr << "Listen failed: " << strerror(errno) << std::endl;
        close(server_fd);
        return 1;
    }

    // Create epoll instance
    int epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        std::cerr << "Epoll creation failed: " << strerror(errno) << std::endl;
        close(server_fd);
        return 1;
    }

    // Add server socket to epoll
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) < 0) {
        std::cerr << "Epoll_ctl failed: " << strerror(errno) << std::endl;
        close(server_fd);
        close(epoll_fd);
        return 1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    // Event loop
    struct epoll_event events[MAX_EVENTS];
    char buffer[BUFFER_SIZE];

    while (true) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (nfds < 0) {
            std::cerr << "Epoll_wait failed: " << strerror(errno) << std::endl;
            break;
        }

        for (int i = 0; i < nfds; i++) {
            int fd = events[i].data.fd;

            if (fd == server_fd) {
                // Handle new connection
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
                if (client_fd < 0) {
                    std::cerr << "Accept failed: " << strerror(errno) << std::endl;
                    continue;
                }

                set_non_blocking(client_fd);
                ev.events = EPOLLIN | EPOLLET; // Edge-triggered
                ev.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) < 0) {
                    std::cerr << "Epoll_ctl failed for client: " << strerror(errno) << std::endl;
                    close(client_fd);
                    continue;
                }

                std::cout << "New connection: " << client_fd << std::endl;
            } else {
                // Handle client data
                while (true) {
                    ssize_t count = read(fd, buffer, BUFFER_SIZE);
                    if (count < 0) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break; // No more data to read
                        }
                        std::cerr << "Read error: " << strerror(errno) << std::endl;
                        close(fd);
                        break;
                    } else if (count == 0) {
                        // Client disconnected
                        std::cout << "Client disconnected: " << fd << std::endl;
                        close(fd);
                        break;
                    } else {
                        // Echo back to client
                        ssize_t sent = write(fd, buffer, count);
                        if (sent < 0) {
                            std::cerr << "Write error: " << strerror(errno) << std::endl;
                            close(fd);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Cleanup
    close(server_fd);
    close(epoll_fd);
    return 0;
}
