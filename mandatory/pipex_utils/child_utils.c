/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:24 by akivam            #+#    #+#             */
/*   Updated: 2025/11/06 15:44:22 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/printf.h"
#include "parser.h"
#include "pipex.h"
#include "pipex_utils.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	check_command_or_exit(t_exec *cmd, t_pipeline *pipeline)
{
	if (!cmd->path || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
	{
		if (cmd->permission)
		{
			ft_err_printf("Permission denied: %s\n", cmd->args[0]);
			free_pipeline(pipeline);
			exit(126);
		}
		ft_err_printf("command not found: %s\n", cmd->args[0]);
		free_pipeline(pipeline);
		exit(127);
	}
}

static void	setup_child_fds(t_pipeline *pipe_data, int i)
{
	int	devnull;

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
}

static void	close_all_pipes(t_pipeline *pipe_data)
{
	int	j;

	j = 0;
	while (j < pipe_data->cmd_count - 1)
	{
		close(pipe_data->pipes[j][0]);
		close(pipe_data->pipes[j][1]);
		j++;
	}
}

void	exec_command_child(t_pipeline *pipe_data, int i)
{
	check_command_or_exit(&pipe_data->commands[i], pipe_data);
	setup_child_fds(pipe_data, i);
	close_all_pipes(pipe_data);
	execve(pipe_data->commands[i].path, pipe_data->commands[i].args,
		pipe_data->envp);
	if (errno == EACCES)
	{
		ft_err_printf("Permission denied: %s\n",
			pipe_data->commands[i].args[0]);
		free_pipeline(pipe_data);
		exit(126);
	}
	ft_err_printf("Error: execve failed.\n");
	free_pipeline(pipe_data);
	exit(127);
}
