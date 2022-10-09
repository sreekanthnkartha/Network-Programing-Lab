#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
	//create socket
	int main_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	//create address
	struct sockaddr_in clie_addr;
	clie_addr.sin_family = AF_INET;
	clie_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clie_addr.sin_port = htons(5550);
	
	//connect
	socklen_t addrlen = sizeof(clie_addr);
	int con = connect(main_sock_fd, (struct sockaddr *)&clie_addr, addrlen);

    if(con<0){
        perror("Connect error");
		exit(1);
    }
	
	char *fname = "input.txt";
	send(main_sock_fd, fname, strlen(fname), 0);
	
	close(main_sock_fd);
		
	return 0;
}