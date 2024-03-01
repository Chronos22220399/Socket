#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUF_SIZE 1024

using std::cin;
using std::cout;
using std::endl;


int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("192.168.1.4");
    servAddr.sin_port = htons(1234);
    
    char buffer[BUF_SIZE];
    sockaddr clintAdddr;
    socklen_t size = sizeof(clintAdddr);
    
    while(1){
        cout << "Input a string: ";
        cin >> buffer;
        sendto(sock, buffer, strlen(buffer) + 1, 0, (sockaddr*)&servAddr, size);
        recvfrom(sock, buffer, BUF_SIZE, 0, (sockaddr*)&clintAdddr, &size);
        cout << "Message from server: " << buffer << endl;
    }
    
    close(sock);
}
