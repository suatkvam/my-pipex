#include "pipex_utils.h"
#include "stdlib.h"
#include "parser.h"

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline || !pipeline->commands)
		return ;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		free_path(pipeline->commands[i].args);
		if (pipeline->commands[i].path)
			free(pipeline->commands[i].path);
		i++;
	}
	free(pipeline->commands);
	if (pipeline->pipes)
	{
		i = 0;
		while (i < pipeline->cmd_count - 1)
		{
			free(pipeline->pipes[i]);
			i++;
		}
		free(pipeline->pipes);
	}
}
