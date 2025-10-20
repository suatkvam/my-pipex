#include "ft_printf/printf.h"
#include "parser.h"
#include "pipex.h"
#include "pipex_utils.h"
#include "stdlib.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

void	check_command_or_exit(t_exec *cmd, t_pipeline *pipeline)
{
	if (!cmd->path || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
	{
		ft_err_printf("command not found: %s\n", cmd->args[0]);
		free_pipeline(pipeline);
		exit(127);
	}
}

void	exec_command_child(t_pipeline *pipe_data, int i)
{
	int	j;
	int	devnull;

	j = 0;
	check_command_or_exit(&pipe_data->commands[i], pipe_data);
	// infile_fd < 0 ise stdin'i /dev/null'a yönlendir
	if (i == 0)
	{
		if (pipe_data->infile_fd < 0)
		{
			devnull = open("/dev/null", O_RDONLY);
			dup2(devnull, STDIN_FILENO);
			close(devnull);
		}
		else
			dup2(pipe_data->infile_fd, STDIN_FILENO);
	}
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
	free_pipeline(pipe_data);
	exit(127);
}

pid_t	spawn_all_children(t_pipeline *pipe_data)
{
	pid_t	last_pid;
	int		i;
	pid_t	pid;

	last_pid = -1;
	i = 0;
	while (i < pipe_data->cmd_count)
	{
		pid = fork();
		if (pid == 0)
			exec_command_child(pipe_data, i);
		if (i == pipe_data->cmd_count - 1)
			last_pid = pid;
		i++;
	}
	i = 0;
	while (i < pipe_data->cmd_count - 1)
	{
		close(pipe_data->pipes[i][0]);
		close(pipe_data->pipes[i][1]);
		i++;
	}
	return (last_pid);
}

int	wait_for_children(pid_t last_pid, int cmd_count)
{
	int		status;
	int		last_status;
	int		i;
	pid_t	wpid;

	last_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		wpid = wait(&status);
		if (wpid == last_pid)
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}
