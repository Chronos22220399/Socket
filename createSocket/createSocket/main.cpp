//
//  main.cpp
//  createSocket
//
//  Created by 无铭 on 2024-01-16.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
using std::cout;
using std::cin;
using std::endl;


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // linux下的socket的原型是：int socket(int af, int type, int protocol)
    // af 为地址族（address family）这里也能写选pf（protocol family)
    // type 为数据传输方式/套接字类型
    // protocol 为协议类型
    int tcp_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(tcp_socket == -1)
        perror("tcp_socket create fail: ");
    
    int udp_socket = socket(PF_INET, SOCK_DGRAM, 0);
    if(udp_socket == -1)
        perror("udp_socket create fail: ");
    // 这里的stream和dgram都只有一种协议能满足条件，所有IPPROTO_TCP和IPPROTO_UDP都可换成0，因为系统会自动推断
    
    // int bind(int sock, const struct sockaddr *addr, int addrlen) 位于<sys/socket.h>
    // 返回 0 表示成功， 返回 -1 表示失败， 调用perror函数可得知失败原因
    
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    struct sockaddr_in serv_addr;
    // 将serv_addr初始化
    memset(&serv_addr, 0, sizeof(serv_addr));
    // 将信息填充进serv_addr
    // use ipv4
    serv_addr.sin_family = AF_INET;
    // use the exact ip address
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // write the port
    serv_addr.sin_port = htons(1234);
    // determine weather the binding is successful
    int isbind = bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(isbind == 0) {
        cout << "binding success" << endl;
    } else {
        perror("binding unsuccess, the result is: ");
    }
    
    
    // connect 函数原型： int connect(int sock, struct sockaddr *serv_addr, socklen_t addrlen)
    
    return 0;
}
