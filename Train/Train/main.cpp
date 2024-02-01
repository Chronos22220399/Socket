//
//  main.cpp
//  Train
//
//  Created by 无铭 on 2024-01-21.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>

using std::cin;
using std::cout;
using std::endl;


int main(int argc, const char * argv[]) {
    // insert code here...
    
    // create a stream socket
    int stream_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(stream_socket == -1){
        perror("stream_socket create fail: ");
    }
    
    // create a dgram socket
    int dgram_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(dgram_socket == -1){
        perror("stream_socket create fail: ");
    }
    
    // create an instance of ip address
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    // bind
    int sock_bind = bind(stream_socket, (sockaddr *)&serv_addr, sizeof(serv_addr));
    if(sock_bind == -1){
        perror("sock_bind failed: ");
    }
    
    return 0;
}
