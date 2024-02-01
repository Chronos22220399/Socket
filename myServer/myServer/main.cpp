//
//  main.cpp
//  myServer
//
//  Created by 无铭 on 2024-01-21.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    // create a socket of server
    int sock_server = socket(PF_INET, SOCK_STREAM, 0);
    // determine weather is create successful
    if(sock_server == -1) {
        perror("socket create failed: ");
        exit(-1);
    }
    
    // binding the ip address with socket
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.0.105");
    serv_addr.sin_port = htons(1234);
    int isbind = bind(sock_server, (sockaddr*)&serv_addr, sizeof(serv_addr));
    if(isbind == -1){
        perror("binding failed: ");
        exit(-1);
    }
    
    // start listening
    int islistening = listen(sock_server, SOMAXCONN);
    
    // create a sockaddr used to store the clint's ipaddress
    // get the clint's socket
    sockaddr_in sock_addr_clint;
    socklen_t sock_addr_clint_size = sizeof(sock_addr_clint);
    int clint_sock = accept(sock_server, (sockaddr*)&sock_addr_clint, &sock_addr_clint_size);
    
    // determine weather accept
    if(clint_sock == -1){
        perror("accept failed: ");
        exit(-1);
    } else {
        char str[20] = "nihao, g";
        write(clint_sock, str, sizeof(str));
    }
    return 0;
    
    // first.  create the server socket
    // second. create the ip address of the server
    // third.  binding the ip address with the server socket
    // forth.  let server socket drop into the state of listening
    // fifth.  let the server socket accept the post sent by clint
    // sixth.  write the info to the clint socket
}
