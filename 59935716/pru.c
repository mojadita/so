
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // just added
#include <netdb.h>//Network address and service translation
#include <arpa/inet.h> //For message type convertion
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/signal.h>
#include <signal.h>
#include <errno.h>

#define BUFFSIZE 2048

// port number
int port_num = 8080;

void handle(int fd) {
    printf("handle function.\n");
    char buff[BUFFSIZE + 1];
    int bytes_read = read(fd, buff, BUFFSIZE);
    printf("bytes_read: %d\n", bytes_read);
    if (bytes_read <= 0) {
        fprintf(stderr, "connection failed, or read failed.\n");
    }
    printf("Msg: %s\n", buff);
    exit(1);
}

int main(int argc, char* argv[]){

    // make sure get the port num
    /*
    if (argc != 2) {
        fprintf(stderr, "Error: Improper number of arguments used\n");
        exit(1);
    }else {
        port_num = atoi(argv[1]);
    }
    */
    // setup socket
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // socket file descriptor
    int fd_server, fd_client;

    char buf[BUFFSIZE];
    int on = 1;

    fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_server < 0) {
        fprintf(stderr, "Error: socket set up failed.\n");
        exit(1);
    }

    // I don't know what is this
    // setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int)); // indeed, you had better not to use it.

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_num);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // binding
    if (bind(fd_server, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        fprintf(stderr, "Error: binding failed.\n");
        exit(1);
    }


    // listen 
    if (listen(fd_server, 10) == -1) {
        fprintf(stderr, "Error: socket listen failed.\n");
        exit(1);
    }

    while (1) {
        // accept

        fd_client = accept(fd_server, (struct sockaddr *)&client_address, &client_address_length);
        if (fd_client == -1) {
            fprintf(stderr, "Error: accept failed.\n");
            continue;
        }
        printf("connected...\n");
        int pid = fork();
        if (!pid) { // check for the value of pid, not call fork() again.
            // child process
            close(fd_server);

            memset(buf, 0, 2048);
            read(fd_client, buf, 2047);
            printf("%s\n", buf);
            close(fd_client);
            printf("closing...\n");
            exit(0);
        }
        close(fd_client);
    }
    return 0;
}
