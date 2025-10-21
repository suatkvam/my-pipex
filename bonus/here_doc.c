#include "ft_printf/printf.h"
#include "./get-next-line/get_next_line_bonus.h"
#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	setup_here_doc(char const *limitter)
{
	int		temp_fd;
	char	*line;

	temp_fd = open(".here_doc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd < 0)
		exit(EXIT_FAILURE);
	ft_printf("pipex here_doc> ");
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strncmp(line, limitter, ft_strlen(limitter) + 1) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		ft_putendl_fd(line, temp_fd);
		free(line);
		ft_printf("pipex here_doc> ");
		line = get_next_line(STDIN_FILENO);
	}
	close(temp_fd);
	get_next_line(-1);
}
