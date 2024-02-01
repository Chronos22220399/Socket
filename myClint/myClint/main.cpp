//
//  main.cpp
//  myClint
//
//  Created by 无铭 on 2024-01-21.
//

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    // create a socket of clint
    int sock_clint = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock_clint == -1){
        perror("create socket failed: ");
        exit(-1);
    }
    
    // create the ip address instance
    // connect the server use server's ip address
    sockaddr_in sock_clint_addr;
    memset(&sock_clint_addr, 0, sizeof(sock_clint_addr));
    sock_clint_addr.sin_family = AF_INET;
    sock_clint_addr.sin_addr.s_addr = inet_addr("192.168.0.105");
    sock_clint_addr.sin_port = htons(1234);
    int isconnect = connect(sock_clint, (sockaddr*)&sock_clint_addr, sizeof(sock_clint_addr));
    
    // determine weather connect
    if(isconnect == -1){
        perror("connect failed: ");
        exit(-1);
    } else {
        char str[20];
        read(sock_clint, str, sizeof(str));
        cout << str << endl;
    }
    return 0;
    
    // first.  create the clint's socket
    // second. binding the ip address of the server
    // third.  connect the ip address and the socket
    // fourth. read the info posted by server
}
