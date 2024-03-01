//
//  main.cpp
//  httpServer
//
//  Created by 无铭 on 2024/2/19.
//

#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFLEN 1024

using std::cin;
using std::cout;
using std::endl;



void startListen();                         // 服务端套接字开始监听

void *threadFun(void *args);                // 线程执行函数

void handle_connect(int& serv_sock);        // 接收客户端的http请求

void http_parse_request_cmd(char *buf, char *file_name, char *suffix);  // 从http请求中提取文件路径

void test(){
//    char str[] = "GET /hello.html HTTP/1.1";
//    char *begin = NULL, *end = NULL, *bias = NULL;
//    // 查找 URL 的开始位置, 包含'/'
//    begin = strchr(str, ' ');
//    begin += 1;
//    cout << begin << endl;
//    end = strchr(begin, ' ');
//    *end = 0;
//    cout << begin << endl;
}

int main(int argc, const char * argv[]) {
    startListen();
    test();

    return 0;
}



void startListen(){
    int serv_sock;
    if((serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
        puts("打开套接字失败");
        exit(-1);
    }
    
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(1234);
    
    if((bind(serv_sock, (sockaddr*)&servAddr, sizeof(servAddr))) == -1){
        // 关闭套接字
        close(serv_sock);
        puts("绑定套接字失败");
        exit(-1);
    }
    
    if((listen(serv_sock, SOMAXCONN)) == -1){
        // 关闭套接字
        close(serv_sock);
        puts("监听出错");
        exit(-1);
    }
}

void * threadFun(void * args) {
    return NULL;
}


void handle_connect(int& serv_sock){
    int clint_sock;
    sockaddr_in clint_addr;
    socklen_t len = sizeof(clint_addr);
    
    while(true){
        clint_sock = accept(serv_sock, (sockaddr*)&clint_addr, &len);
        
        // 接收成功则创建新的线程处理信息
        if(clint_sock > 0){
            pthread_t myThread;
            int ret;
            
            // threadFun 为线程要执行的函数，clint_sock为threadFun的参数
            ret = pthread_create(&myThread, NULL, threadFun, &clint_sock);
            
            if(ret != 0){
                puts("创建线程失败");
                exit(-1);
            }
        }
    }
}

void http_parse_request_cmd(char *buf, char *file_name, char *suffix){
    int file_length = 0, suffix_length = 0;
    char *begin = NULL, *end = NULL, *bias = NULL;
    // 查找 URL 的开始位置, 包含'/'
    begin = strchr(buf, ' ');
    begin += 1;
    end = strchr(begin, ' ');
    *end = 0;
    file_length = end - begin - 1;
    // file_name 不包括'\'
    memcpy(file_name, begin + 1, file_length);
}
