#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#define time_wait 3
/*typedef struct packet{
    char data[1024];
}Packet;

typedef struct frame{
   int frame_kind; //ACK:0, SEQ:1 FIN:2
    int sq_no;
    //char ack;
    Packet packet;
}Frame;*/

int main(int argc, char **argv){
    if (argc != 2){
		printf("Usage: %s <port>", argv[0]);
		exit(0);	
	}
    int flag=0;
	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	socklen_t addr_size;

	//int frame_id = 0;
	//Frame frame_send;
	//Frame frame_recv;
	int ack_recv = 0;
    time_t begin,end;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	while(1){
		
		if(ack_recv == 0){
		/*	frame_send.sq_no = frame_id;
			frame_send.frame_kind = 1;
			frame_send.ack = 0;		*/
	        memset(&buffer, '\0', sizeof(buffer));
			printf("Enter Data: for packet 0\n");
			scanf("%s", buffer);
            buffer[strlen(buffer)]='0';
			//strcpy(frame_send.packet.data, buffer);
			sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			printf("[+]Frame Send\n");
            begin = time(NULL);
            memset(&buffer, '\0', sizeof(buffer));
            
		}
        else 
        {
       /*   frame_send.sq_no = frame_id;
			frame_send.frame_kind = 1;
			frame_send.ack = 0;		*/
	        memset(&buffer, '\0', sizeof(buffer));
			printf("Enter Data: for packet 1\n");
			scanf("%s", buffer);
            buffer[strlen(buffer)]='1';
			//strcpy(frame_send.packet.data, buffer);
			sendto(sockfd, &buffer, sizeof(buffer), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			printf("[+]Frame Send\n"); 
            begin = time(NULL);
            memset(&buffer, '\0', sizeof(buffer));
		}
		int addr_size = sizeof(serverAddr);
        end = time(NULL);
        while(end - begin < time_wait)
        {
            
            memset(&buffer, '\0', sizeof(buffer));            
            end = time(NULL);;        
    		int f_recv_size = recvfrom(sockfd, &buffer, sizeof(buffer), 0 ,(struct sockaddr*)&serverAddr, &addr_size);
            if(f_recv_size <0)
            {
                printf("Still waiting\n");
                sleep(500);
            }
            else
            {
                flag=1;
                //strcpy(buffer,frame_recv.packet.data);
                //printf("Buffer received\n");
                int len=strlen(buffer);
                printf("%.*s\n",len-1,buffer+0);
                //printf("%s\n",buffer);
                break;
            }
        }
		if(flag==0)
        {
            printf("Time out send again\n");
            ack_recv=ack_recv;
        }
        else
        {
            if(buffer[strlen(buffer)-1]=='$')
            {
                printf("Already Received send new \n");
                ack_recv=ack_recv ^ 1;
            }
            else if(buffer[strlen(buffer)-1]=='0')
            {
                ack_recv=0;
                printf("Send the packet no %d \n",ack_recv);
            }
            else
            {
                ack_recv=1;
                printf("Send the packet no %d \n",ack_recv);
            }
        }
        flag=0;
	/*	if( f_recv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frame_id+1){
			printf("[+]Ack Received\n");
			ack_recv = 1;
		}else{
			printf("[-]Ack Not Received\n");
			ack_recv = 0;
		}	*/
  			memset(&buffer, '\0', sizeof(buffer));
		//frame_id++;		
	}
	
	close(sockfd);
	return 0;
}
