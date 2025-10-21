#include "pipex.h"
#include "printf.h"
#include "unistd.h"
#include <stdlib.h>

static void	free_pipes_on_err(int ***pipes, int n)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if ((*pipes)[i])
			free((*pipes)[i]);
	}
	free((*pipes));
}

int	create_pipes(int ***pipes, int n)
{
	int	i;

	*pipes = malloc(sizeof(int *) * n);
	if (!*pipes)
	{
		ft_err_printf("Error: memory allocation failed for pipes.\n");
		return (1);
	}
	i = -1;
	while (++i < n) // TODO: bu dışarı çıkacak
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
		{
			ft_err_printf("Error: memory allocation failed for pipe.\n");
			free_pipes_on_err(pipes, i);
			return (1);
		}
		if (pipe((*pipes)[i]) == -1)
		{
			ft_err_printf("Error: pipe creation failed.\n");
			free_pipes_on_err(pipes, i + 1);
			return (1);
		}
	}
	return (0);
}
