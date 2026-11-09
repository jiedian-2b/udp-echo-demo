#include <sys/types.h>
#include <sys/socket.h>
#include<stdio.h>
#include <netinet/in.h>   // ✅ 主要：struct sockaddr_in、AF_INET、htons、htonl、INADDR_ANY
#include <sys/socket.h>   // ✅ socket、bind、recvfrom、sendto、struct sockaddr
#include <arpa/inet.h>    // ✅ inet_pton / inet_ntop（IP字符串和二进制转换）
#include<string.h>
#include <unistd.h>


#define BUF_SIZE 1024

int main()
{
    //创建网络套接字文件
    int fd=socket(AF_INET,SOCK_DGRAM,0 );
    struct sockaddr_in addr_in;
    struct sockaddr_in cli_addr;
    if(fd<0)
    {
        //创建套接字失败
        perror("创建套接字失败");
        return -1;
    }
    memset(&addr_in,0,sizeof(addr_in));

    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(8888);
    addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t addr_in_size=sizeof(addr_in);
    socklen_t cli_addr_size=sizeof(cli_addr);
    int res= bind(fd, (struct sockaddr *)&addr_in,addr_in_size );
    char rec_buf [BUF_SIZE];
    
    if(res<0)
    {
        //socket文件没有绑上对应的端口IP
        perror("socket文件没有绑上对应的端口IP");
        close(fd);
        return -2;
    }

    while(1)
    {
        int rec_num=recvfrom(fd, rec_buf,BUF_SIZE-1 , 0,
                (struct sockaddr *) &cli_addr,&cli_addr_size );

    if(rec_num<0)
    {
        //没有从客户端拿到信息
        perror("没有从客户端拿到数据\n");
        close(fd);
        return -3;
    }

    printf("收到数据,%s",rec_buf);
    sendto(fd, rec_buf, BUF_SIZE-1, 0,
               (struct sockaddr *) &cli_addr,sizeof(cli_addr));


    }

    close(fd);
    return 0;
}



