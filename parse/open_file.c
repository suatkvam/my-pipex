#include <fcntl.h>
#include <stdio.h>

int	open_file(const char *file_name, int flags, int mode)
{
	int	fd;

	fd = open(file_name, flags, mode);
	if (fd < 0)
    {
        perror("");
		return (-1);
    }
	return (fd);
}
