//
//  main.cpp
//  whileServer
//
//  Created by 无铭 on 2024-01-24.
//

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(server_socket == -1){
        perror("server_socket创建失败");
        exit(-1);
    }
    
    // 实现端口复用
    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt, sizeof(opt));
    
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(1234);
    int isbind = bind(server_socket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if(isbind == -1){
        perror("绑定失败");
        exit(-1);
    }
    
    int islisten = listen(server_socket, SOMAXCONN);
    if(islisten == -1){
        perror("监听失败");
        exit(-1);
    }
    
    sockaddr_in sockAddr;
    socklen_t len = sizeof(sockAddr);
    int clint_socket = accept(server_socket, (sockaddr*)&sockAddr, &len);
    
    char str[30];
    sleep(8);
    // 注意这里，让程序暂停10秒
    // 接收客户端发来的数据，并原样返回
    recv(clint_socket, str, 30, 0);
    cout << "从客户端传递来的数据：" << str << endl;
    send(clint_socket, str, 30, 0);

    
    close(clint_socket);
    close(server_socket);
    return 0;
}
