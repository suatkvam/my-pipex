/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:07 by akivam            #+#    #+#             */
/*   Updated: 2025/10/22 17:50:51 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include <sys/wait.h>
#include "../ft_printf/printf.h"
#include <unistd.h>

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
    int		nonzero_status;
    int		i;
    pid_t	wpid;

    last_status = 0;
    nonzero_status = 0;
    i = 0;
    while (i < cmd_count)
    {
        wpid = waitpid(-1, &status, 0);
        if (wpid == -1)
        {
            ft_err_printf("Error: waitpid failed.\n");
            return (1);
        }
        /* capture any non-zero exit status (prefer to return it) */
        if (WIFEXITED(status))
        {
            if (WEXITSTATUS(status) != 0)
                nonzero_status = WEXITSTATUS(status);
        }
        if (wpid == last_pid)
            last_status = status;
        i++;
    }
    if (nonzero_status != 0)
        return (nonzero_status);
    if (WIFEXITED(last_status))
        return (WEXITSTATUS(last_status));
    return (1);
}
