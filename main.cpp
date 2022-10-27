#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>

#include <thread>  
#define PORT 8000

 void get_message(int sock, char *buffer){
    while (true){
        recv(sock, buffer, 1024, 0);
        printf("%s\n", buffer);
    }
}

void send_mesagge(int sock){
    while (true){
        printf("Enter message:\n");
        std::string str;
        std::getline(std::cin, str);
        char* cstr = strdup(str.c_str());
        send(sock, cstr, strlen(cstr) , 0);
        delete [] cstr;
    }
}
 
int main(int argc, char const* argv[])
{
    char ip_adres_server[] = "127.0.0.1";
    int sock = 0, valread, client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, ip_adres_server, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((client_fd = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    std::thread send(send_mesagge, sock);
    std::thread get(get_message, sock, buffer);

    send.join();
    get.join();

    return 0;
}