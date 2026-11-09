#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define S_BUFF 1024

int main()
{
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    if(fd<0)
    {
        //创建套接字失败
        return -1;
    }
    char send_buf[S_BUFF];
    char rec_buf[S_BUFF];
    struct sockaddr_in server_dest;
    memset(&server_dest, 0, sizeof(server_dest));
    server_dest.sin_family=AF_INET;
    server_dest.sin_port=htons(8888);
    server_dest.sin_addr.s_addr = inet_addr("127.0.0.1");

    struct sockaddr_in client_src;
    memset(&client_src, 0, sizeof(client_src));
    


    while(1)
    {
        fgets(send_buf,S_BUFF,stdin);//得到键盘输入
        int st=sendto(fd,send_buf,S_BUFF-1,0,(struct sockaddr *)&server_dest,sizeof(server_dest));
        if(st<0)
        {
            perror("sendto");
            continue;
        }
        socklen_t client_size=sizeof(client_src);
        int rt=recvfrom(fd, rec_buf,S_BUFF-1 , 0,
                (struct sockaddr *) &client_src,&client_size );

        if(rt<0)
        {
            perror("recvfrom");
            continue;
        }
        rec_buf[S_BUFF]='\0';
        printf("接收到数据：%s",rec_buf);

        
    }
    close(fd);
    return 0;
}