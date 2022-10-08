#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	// create socket
	int main_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (main_sock_fd < 0)
	{
		printf("socket creation error\n");
		exit(1);
	}

	// create address
	struct sockaddr_in serv_addr, clie_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(5550);

	// create bind
	if (bind(main_sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("Bind Error");
		exit(1);
	}

	// create listen
	if (listen(main_sock_fd, 10) < 0)
	{
		perror("Listen Error");
		exit(1);
	}

	int new_sock_fd;

	while (1)
	{
		socklen_t addrlen = sizeof(clie_addr);
		new_sock_fd = accept(main_sock_fd, (struct sockaddr *)&clie_addr, &addrlen);

		if (new_sock_fd < 0)
		{
			// perror("Accept Error");
			break;
		}

		printf("Connection Established\n");

		close(main_sock_fd);
		int childpid;
		if (childpid = fork() == 0)
		{
			char fname[100], *f1 = "output.txt";

			int len = recv(new_sock_fd, fname, 100, 0);
			fname[len] = '\0';

			printf("%s\n", fname);

			if (access(fname, F_OK) != 0)
			{
				printf("No file found\n");
				exit(1);
			}

			FILE *fp = fopen(fname, "r");
			FILE *fp1 = fopen(f1, "w");

			int pid = getpid();
			char pid_c[100], buffer[100];
			sprintf(pid_c, "%d", pid);
			printf("%d\n", pid);

			int count = 0;

			while (!feof(fp))
			{
				fscanf(fp, "%s", buffer);
				count++;
				printf("%s\n", buffer);
				fprintf(fp1, "%s ", buffer);
			}
			fprintf(fp1, "\nPID : %d", pid);
			printf("%d", count);
		}
		close(new_sock_fd);
	}
	close(new_sock_fd);
	return 0;
}