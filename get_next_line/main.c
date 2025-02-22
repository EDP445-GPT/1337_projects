#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("file.txt", O_RDWR);
	char buffer[14];

	read(fd, buffer, 14);
	write(fd, "my", );
}