#include "pipex_utils.h"
#include "stdlib.h"

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline || !pipeline->commands)
		return ;
	for (int i = 0; i < pipeline->cmd_count; i++)
	{
		free_path(pipeline->commands[i].args);
		if (pipeline->commands[i].path)
			free(pipeline->commands[i].path);
	}
	free(pipeline->commands);
	if (pipeline->pipes)
	{
		for (int i = 0; i < pipeline->cmd_count - 1; i++)
			free(pipeline->pipes[i]);
		free(pipeline->pipes);
	}
}