#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <exception>
#include <stdlib.h>

#define BUFFLEN 1024
#define HTTP_REQ 256
#define FILE_TYPE 16

using std::cin;
using std::cout;
using std::endl;
using std::exception;

struct doc_type {
    char const * suffix;
    char const * type;
};

doc_type http_file_type[] = {
    {"html", "text/html"},
    {"ico", "image/x-icon"},
    {NULL, NULL}
};


char http_res_hdr_tmpl[] = "HTTP/1.1 200 OK\nServer: DianLanZhiRan\n"
                           "Accept-Ranges: bytes\nContent-Length: %d\nConnection: closed\n"
                           "Content-Type: %s\nContent-Disposition: inline\n\n";




void handle_connect(int &serv_sock);

void* ThreadFunc(void *args);

char * http_get_type_by_suffix(char * suffix);

void http_parse_request(char * buff, char * file_name, char * suffix);

int main(){
    int serv_sock;
    if((serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1){
        puts("serv_sock创建失败");
        exit(-1);
    }
    
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(1234);
    
    // 绑定套接字
    if(bind(serv_sock, (sockaddr*)&servAddr, sizeof(servAddr)) == -1){
        puts("套接字绑定失败\n正在关闭serv_sock...");
        close(serv_sock);
        exit(-1);
    }
    
    // 监听套接字
    if(listen(serv_sock, SOMAXCONN) == -1){
        puts("套接字监听出错\n正在关闭serv_sock...");
        close(serv_sock);
        exit(-1);
    }
    
    handle_connect(serv_sock);
    close(serv_sock);
    return 0;
}


void http_parse_request(char * buff, char * file_name, char * suffix){
    char *begin = NULL, *end = NULL, *bias = NULL;
    unsigned long file_length, suffix_length;
    
    begin = strchr(buff, ' ');
    // 定位到'/'处
    begin += 2;
    
    end = strchr(begin, ' ');
    *end = 0;
    // 获取文件长度
    file_length = end - (begin - 1);
    cout << begin << endl;
    strcpy(file_name, begin);
    bias = strchr(begin, '.');
    if(bias){
        bias++;
        suffix_length = end - bias;
        strcpy(suffix, bias);
    } else {
        if(bias - end > 0)
            suffix = NULL;
    }
}


void* ThreadFunc(void *args){
    pthread_detach(pthread_self());
    int clint_sock = *(int *)args;
    char request[HTTP_REQ] = {0};
    unsigned long nCount;
    unsigned long num;
    // 读取http请求
    num = read(clint_sock, request, HTTP_REQ);
    
    if(num > 0){
        FILE *fp = NULL;
        char file_name[HTTP_REQ], suffix[FILE_TYPE];
        // 文件长度，http响应行、响应头长度
        unsigned long file_length, hdr_length;
        char const *type = NULL;
        char http_header[HTTP_REQ];
        char buff[BUFFLEN] = {0};
        
        // 获取文件名，文件类型
        http_parse_request(request, file_name, suffix);
        type = http_get_type_by_suffix(suffix);
        cout << file_name << endl << suffix << endl;
        if(type){
            fp = fopen(file_name, "rb");
            if(!fp){
                puts("文件不存在");
                fp = fopen("errno.html", "rb");
                type = "html";
            } else {
                puts("文件存在，正在打开文件");
            }
        } else {
            cout << type << endl;
            puts("文件类型错误");
            fp = fopen("errno.html", "rb");
        }
        
        // 计算文件的大小
        fseek(fp, 0, SEEK_END);
        file_length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        hdr_length = snprintf(http_header, HTTP_REQ, http_res_hdr_tmpl, file_length, type);
        
        write(clint_sock, http_header, hdr_length);
        
        // 传输文件
        memset(buff, 0, BUFFLEN);
        while((nCount = fread(buff, 1, BUFFLEN, fp)) > 0){
            write(clint_sock, buff, nCount);
            memset(buff, 0, nCount + 1);
        }
        
        fclose(fp);
        shutdown(clint_sock, SHUT_WR);
        read(clint_sock, buff, BUFFLEN);
        close(clint_sock);
    }
    return NULL;
}

void handle_connect(int &serv_sock){
    int clint_sock;
    sockaddr_in clintAddr;
    socklen_t len = sizeof(clintAddr);
    
    while(true){
        clint_sock = accept(serv_sock, (sockaddr*)&clintAddr, &len);
        
        if(clint_sock > 0){
            int ret;
            pthread_t myThread;
            ret = pthread_create(&myThread, NULL, ThreadFunc, &clint_sock);
            
            if(ret != 0){
                puts("线程创建失败");
                exit(-3);
            }
        }
    }
}


char * http_get_type_by_suffix(char * suffix){
    doc_type *type = NULL;
    for(type = http_file_type; type->suffix; ++type){
        if(strcmp(type->suffix, suffix) == 0) {
            return (char*)type->suffix;
        }
    }
    return NULL;
}
