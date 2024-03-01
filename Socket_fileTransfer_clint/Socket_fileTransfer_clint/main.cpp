//
//  main.cpp
//  Socket_fileTransfer_clint
//
//  Created by 无铭 on 2024/2/10.
//

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;


int main(int argc, const char * argv[]) {
    char filename[] = "";
    FILE *fp = fopen(filename, "wb");
    if(fp == NULL){
        puts("Cannot open file");
        exit(-1);
    }
    
    int clint_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(1234);
    
    connect(clint_sock, (sockaddr*)&server_addr, sizeof(server_addr));
    char fileContent[1024];
    int nCount;
    
    while((nCount = read(clint_sock, fileContent, 1024)) > 0){
        fwrite(fileContent, nCount, 1, fp);
    }
    
    fclose(fp);
    close(clint_sock);
    return 0;
}
