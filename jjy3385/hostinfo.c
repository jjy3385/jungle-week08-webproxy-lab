#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char **argv)
{   

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        return 1;
    }

    const char *name = argv[1];
    struct addrinfo hints, *listp = NULL, *p = NULL;

    char buf[1024];
    char host[1024];
    int rc;
    
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    rc = getaddrinfo(name, NULL, &hints, &listp);
    if (rc != 0) {
        fprintf(stderr, "getaddinfo error: %s\n", gai_strerror(rc));
        return 1;
    }

    int flags = NI_NUMERICHOST | AI_CANONNAME;
    for (p = listp; p; p = p->ai_next) {

        printf("flags: %d\n", p->ai_flags);
        printf("family: %d\n", p->ai_family);
        printf("socktype: %d\n", p->ai_socktype);
        printf("protocol: %d\n", p->ai_protocol);
        printf("addrlen: %d\n", (int)p->ai_addrlen);

        if (p->ai_canonname) {
            printf("canonname: %s\n", p->ai_canonname);
        }

        rc = getnameinfo(p->ai_addr,p->ai_addrlen,buf,sizeof(buf),host,sizeof(host),flags);
        if (rc != 0) {
            fprintf(stderr, "getnameinfo error: %s\n", gai_strerror(rc));
        } else {
            printf("host: %s\n",buf);
            printf("service/port: %s\n",host);    
        }

        puts("--------------------------");
    }
    freeaddrinfo(listp);
    return 0;
}