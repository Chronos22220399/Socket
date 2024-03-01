//
//  UDP.cpp
//  Socket_fileTransfer_server
//
//  Created by 无铭 on 2024/2/11.
//

#include "UDP.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


void useUDP_server(){
//    创建udp套接字
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    sockaddr_in saddr;
    memchr(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
//    获取本机ip
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(1234);
    bind(sock, (sockaddr*)&saddr, sizeof(saddr));
    
    sockaddr clint_addr;
    char buffer[1024];
    socklen_t len = sizeof(clint_addr);
    
    while(1){
        ssize_t strlen = recvfrom(sock, buffer, 1024, 0, &clint_addr, &len);
        sendto(sock, buffer, strlen, 0, &clint_addr, len);
    }
    close(sock);
}
