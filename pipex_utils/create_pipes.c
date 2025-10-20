#include "pipex.h"
#include "printf.h"
#include "unistd.h"
#include <stdlib.h>

int	create_pipes(int ***pipes, int n)
{
	int	i;

	*pipes = malloc(sizeof(int *) * n);
	if (!*pipes)
	{
		ft_err_printf("Error: memory allocation failed for pipes.\n");
		return (1);
	}
	i = 0;
	while (i < n)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
		{
			ft_err_printf("Error: memory allocation failed for pipe.\n");
			return (1);
		}
		if (pipe((*pipes)[i]) == -1)
		{
			ft_err_printf("Error: pipe creation failed.\n");
			return (1);
		}
		i++;
	}
	return (0);
}
