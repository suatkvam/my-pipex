/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:15 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 18:50:16 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

# include "../pipex.h"
# include <sys/types.h>
# include <unistd.h>

typedef struct s_pipeline
{
	t_exec		*commands;
	int			**pipes;
	int			infile_fd;
	int			outfile_fd;
	int			cmd_count;
	char *const	*envp;
}				t_pipeline;

void		check_command_or_exit(t_exec *cmd, t_pipeline *pipeline);
pid_t		spawn_all_children(t_pipeline *pipe_data);
int			wait_for_children(pid_t last_pid, int cmd_count);
int			create_pipes(int ***pipes, int n);
void		exec_command_child(t_pipeline *pipe_data, int i);
void		free_pipeline(t_pipeline *pipeline);
void		exec_command_child(t_pipeline *pipe_data, int i);
void		check_command_or_exit(t_exec *cmd, t_pipeline *pipeline);

#endif