#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: showip hostname\n");
        return 1;
    }

    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 2;
    }

    std::cout << "IP address for " << argv[1] << "\n\n";

    for(p = res; p!=NULL; p = p->ai_next){
        void *addr;
        std::string ipver;

        if(p->ai_family == AF_INET){
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = std::string("IPV4");
        } else{
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = std::string("IPV6");
        }  

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        std::cout << ipver << ": " << ipstr << "\n";
    }

    freeaddrinfo(res); // 釋放鏈結串列

    return 0;

}