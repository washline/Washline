#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void DisplayMenu()
{
	printf("*********************\n");
	printf("1. Create File       \n");
	printf("2. Write to File     \n");
	printf("0. Quit              \n");
	printf("*********************\n");
}

int main()
{
	char file_name[20] = {0};
	char buf[256] = {0};
	int  fd;
	ssize_t nbytes;
	int choice;

	while (1)
	{
		DisplayMenu();
		printf("Your choice: ");
		scanf("%d", &choice);
		
		if (0 == choice)
		{
			printf("Thank your for using!\n");
			break;
		}
		switch (choice)
		{
			case 1:
				printf("Please input new file's name:");
				scanf("%s", file_name);

				fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				if (-1 == fd)
				{
					if (EEXIST == errno)
					{
						printf("This file(%s) has already existed!\n", file_name);
						continue;
					}
					else
					{
						perror("open file error");
						return -1;	
					}
				}
				
				close(fd);
				printf("Create OK!\n");
				break;
			case 2:
				printf("Please input file's name:");
				scanf("%s", file_name);
				
				fd = open(file_name, O_WRONLY | O_APPEND);
				if (-1 == fd)
				{
					perror("open file error");
					return -1;
				}
			
				printf("Please input some words to %s file:\n", file_name);
				scanf("%s", buf);
				buf[strlen(buf)] = '\0';
	
				nbytes = write(fd, buf, strlen(buf));
				if (-1 == nbytes)
				{
					perror("write file error");
					return -1;
				}

				close(fd);
				printf("Write OK!\n");
				break;
			default:
				printf("Invalid choice!\n");
		}
	}

	return 0;
}
