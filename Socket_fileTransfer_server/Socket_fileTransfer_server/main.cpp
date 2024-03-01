//
//  main.cpp
//  Socket_fileTransfer_server
//
//  Created by 无铭 on 2024/2/10.
//


#include "UseHostnameInSocket.hpp"




int main(int argc, const char * argv[]) {
    useHostname();
    return 0;
}



void useSocketTransFile(){
    int server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
// 连接服务端的套接字和地址
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(1234);
    int isbind = bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr));
    
//    开始监听
    listen(server_sock, SOMAXCONN);
    
//    接受用户端
    sockaddr_in clint_addr;
    socklen_t len = sizeof(clint_addr);
    int clint_sock = accept(server_sock, (sockaddr*)&clint_addr, &len);
    
    char filename[] = "/Users/wuming/Desktop/实习报告模板.doc";
    char buffer[1024];
    FILE *fp = fopen(filename, "rb");
    if(fp == NULL){
        puts("Cannot open file");
        exit(-1);
    }
    int nCount;
    while((nCount = fread(buffer, 1, 1024, fp)) > 0){
        send(clint_sock, buffer, nCount, 0);
    }
    
    shutdown(clint_sock, SHUT_WR);
    
    fclose(fp);
    close(server_sock);
    close(clint_sock);
}
