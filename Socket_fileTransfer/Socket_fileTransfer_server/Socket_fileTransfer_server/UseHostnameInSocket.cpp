//
//  UseHostnameInSocket.cpp
//  Socket_fileTransfer_server
//
//  Created by 无铭 on 2024/2/11.
//

#include "UseHostnameInSocket.hpp"


void useHostname() {
    struct addrinfo *result;
    struct addrinfo hints;

    // 清空hints结构体，并设置相关参数
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     // AF_INET 或 AF_INET6，取决于IPv4或IPv6
    hints.ai_socktype = SOCK_STREAM; // 套接字类型，这里使用流套接字

    int status = getaddrinfo("www.baidu.com", NULL, &hints, &result);

    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    // 遍历addrinfo链表
    for (struct addrinfo *p = result; p != NULL; p = p->ai_next) {
        printf("Address type: %s\n", (p->ai_family == AF_INET) ? "AF_INET" : "AF_INET6");

        // 获取IP地址
        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            printf("IP addr: %s\n", inet_ntoa(ipv4->sin_addr));
        } else {
            // 处理IPv6的情况
        }
    }

    freeaddrinfo(result);
}
