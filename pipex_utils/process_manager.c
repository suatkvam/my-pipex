#include "ft_printf/printf.h"
#include "pipex_utils.h"
#include <sys/wait.h>
#include <unistd.h>

void	exec_command_child(t_pipeline *pipe_data, int i)
{
	int	j;

	j = 0;
	if (i == 0)
		dup2(pipe_data->infile_fd, STDIN_FILENO);
	else
		dup2(pipe_data->pipes[i - 1][0], STDIN_FILENO);
	if (i == pipe_data->cmd_count - 1)
		dup2(pipe_data->outfile_fd, STDOUT_FILENO);
	else
		dup2(pipe_data->pipes[i][1], STDOUT_FILENO);
	while (j < pipe_data->cmd_count - 1)
	{
		close(pipe_data->pipes[j][0]);
		close(pipe_data->pipes[j][1]);
		j++;
	}
	execve(pipe_data->commands[i].path, pipe_data->commands[i].args,
		pipe_data->envp);
	ft_err_printf("Error: execve failed.\n");
	exit(1);
}

void	spawn_all_children(t_pipeline *pipe_data)
{
	int		i;
	int		j;
	pid_t	pid;

	i = 0;
	while (i < pipe_data->cmd_count)
	{
		pid = fork();
		if (pid == 0)
			exec_command_child(pipe_data, i);
		i++;
	}
	j = 0;
	while (j < pipe_data->cmd_count - 1)
	{
		close(pipe_data->pipes[j][0]);
		close(pipe_data->pipes[j][1]);
		j++;
	}
	i = 0;
	while (i < pipe_data->cmd_count)
	{
		wait(NULL);
		i++;
	}
}

int	manage_pipeline(t_pipeline *pipe_data)
{
	spawn_all_children(pipe_data);
	return (0);
}
