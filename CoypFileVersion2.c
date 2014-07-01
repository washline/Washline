#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd_in, fd_out;
	char c[8] = {0};
	ssize_t nrbytes, nwbytes;

	fd_in = open("a.pdf", O_RDONLY);
	if (-1 == fd_in)
	{
		perror("open");
		return -1;
	}
	
	fd_out = open("b.pdf", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (-1 == fd_out)
	{
		perror("open");
		return -1;
	}

	while (1)
	{
		nrbytes = read(fd_in, c, sizeof(c));
		if (-1 == nrbytes)
		{
			perror("read");
			return -1;
		}
		
		if (0 == nrbytes)
		{
			break;
		}
		
		nwbytes = write(fd_out, c, nrbytes);
		if (-1 == nwbytes)
		{
			perror("write");
			return -1;
		}
	}

	return 0;
}
