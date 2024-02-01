//
//  main.cpp
//  whileClint
//
//  Created by 无铭 on 2024-01-24.
//

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    
    connect(sock, (sockaddr*)&sockAddr, sizeof(sockAddr));
    
    
//    char bufSend[30] = {0};
//    printf("Input a string: ");
//    cin >> bufSend;
//    for(int i=0; i<3; i++){
//        send(sock, bufSend, strlen(bufSend), 0);
//    }
//    //接收服务器传回的数据
//    char bufRecv[30] = {0};
//    recv(sock, bufRecv, 30, 0);
//    //输出接收到的数据
//    printf("Message form server: %s\n", bufRecv);
//    close(sock);  //关闭套接字
    
    char str[30];
    cin >> str;
    cout << "还未读入时：" << str << endl;
    for(int i = 0; i < 3; ++i) {
        //传入的长度必须小于字符串本身的长度，如果传入的长度大于字符串的长度时，字符串末尾的'\0'就不会被覆盖掉，在服务端接收时遇到了'\0'就会停止接收
        send(sock, str, 2, 0);
    }
    char strr[30];
    recv(sock, strr, 30, 0);
    cout << "从服务端读取数据后：" << strr << endl;
    close(sock);
    
    return 0;
}
//    //获取用户输入的字符串并发送给服务器
//    char bufSend[30] = {0};
//    printf("Input a string: ");
//    cin >> bufSend;
//    for(int i=0; i<3; i++){
//        send(sock, bufSend, strlen(bufSend), 0);
//    }
//    //接收服务器传回的数据
//    char bufRecv[30] = {0};
//    recv(sock, bufRecv, 30, 0);
//    //输出接收到的数据
//    printf("Message form server: %s\n", bufRecv);
//    close(sock);  //关闭套接字
