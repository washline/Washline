#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd_in, fd_out;
	char c;
	ssize_t ret;

	fd_in = open("text.txt", O_RDONLY);
	if (-1 == fd_in)
	{
		perror("open");
		return -1;
	}
	
	fd_out = open("b.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == fd_out)
	{
		perror("open");
		return -1;
	}

	while (1)
	{
		ret = read(fd_in, &c, 1);
		if (-1 == ret)
		{
			perror("read");
			return -1;
		}
		
		if (0 == ret)
		{
			break;
		}
		
		ret = write(fd_out, &c, 1);
		if (-1 == ret)
		{
			perror("write");
			return -1;
		}
	}

	return 0;
}

