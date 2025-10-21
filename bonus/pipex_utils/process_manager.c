/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:13 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 18:51:14 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/printf.h"
#include "pipex_utils.h"
#include <sys/wait.h>
#include <unistd.h>

static void	spawn_children(t_pipeline *pipe_data, int here_doc, pid_t *last_pid)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < pipe_data->cmd_count)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_err_printf("Error: fork failed.\n");
			free_pipeline(pipe_data);
			exit(1);
		}
		if (pid == 0)
			exec_command_child(pipe_data, i, here_doc);
		if (i == pipe_data->cmd_count - 1)
			*last_pid = pid;
		i++;
	}
}

static void	close_pipes(t_pipeline *pipe_data)
{
	int	i;

	i = 0;
	while (i < pipe_data->cmd_count - 1)
	{
		close(pipe_data->pipes[i][0]);
		close(pipe_data->pipes[i][1]);
		i++;
	}
}

pid_t	spawn_all_children(t_pipeline *pipe_data, int here_doc)
{
	pid_t	last_pid;

	last_pid = -1;
	spawn_children(pipe_data, here_doc, &last_pid);
	close_pipes(pipe_data);
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
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
		{
			ft_err_printf("Error: waitpid failed.\n");
			return (1);
		}
		if (wpid == last_pid)
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}
