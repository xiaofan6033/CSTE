//gcc -g -fno-stack-protector geshihua.c -o geshihua
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


char string[1000];

int server_sockfd;//服务器端套接字
int client_sockfd;//客户端套接字
int len;
struct sockaddr_in my_addr;//服务器网络地址结构
struct sockaddr_in remote_addr;//客户端网络地址结构体
int sin_size;
char buf[BUFSIZ];//数据传送的缓冲区

void socketConnect(){

    memset(&my_addr,0,sizeof(my_addr));//数据初始化 清零
    my_addr.sin_family = AF_INET;//设置为IP通 信
    my_addr.sin_addr.s_addr = INADDR_ANY;//服务器IP地址，允许连接到所有本地地址上
    my_addr.sin_port = htons(41017);//服务器端口号需提取
    
    
    /* 创建服务器端套接字  IPV4协议,面向链接痛心，tcp*/
    if((server_sockfd = socket(PF_INET,SOCK_STREAM,0))<0){
        perror("socket");
        return 1;
    }
    
    /*将套接字绑定到服务器的网络地址上*/
    if(bind(server_sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0){
        perror("bind");
        return 1;
    }
    
    /*监听链接请求  监听队列长度为5*/
    listen(server_sockfd,5);
    
    sin_size = sizeof(struct sockaddr_in);
    
    
    /*等待客户端连接请求到达*/
    if((client_sockfd = accept(server_sockfd,(struct sockaddr *)&remote_addr,&sin_size))<0){
        perror("accpet");
        return 1;
    }
    
    printf("accept client %s\n",inet_ntoa(remote_addr.sin_addr));
    strcpy(string,"welcome to my server\n");
    len  = send(client_sockfd,string,strlen(string),0);//发送欢迎信息
}



int main(void)
{ 
    socketConnect();   

    int flag = 9;
    int *p = &flag; 
    char a[100];
    //scanf("%s",a);
    len = recv(client_sockfd,a,100,0);
    printf(a);
    if(flag == 2000)
    {
        //printf("good!!\n");
        system("ls");
    }
    //bbbb%p.%p.%p.%p.%p.%p
    //bbbb%x.%x.%x.%x.%x.%x
    
    printf("\n%d\n",*p);
    return 0;
}

