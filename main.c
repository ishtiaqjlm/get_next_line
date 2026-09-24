#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("big_line_with_nl.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	//printf("[%s]", line);
	//free(line);
	while (line)
	{
		printf("[%s]", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
