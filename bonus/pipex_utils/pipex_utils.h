/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:16 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 19:02:06 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

# include "../pipex.h"
# include <sys/types.h>
# include <unistd.h>

void	open_in_out_files(t_pipeline *pipeline, char const *infile,
			char const *outfile, int here_doc);
void	setup_pipeline(t_pipeline *pipeline, char const *argv[],
			char const *envp[], int here_doc);
void	setup_here_doc(char const *limitter);
pid_t	spawn_all_children(t_pipeline *pipe_data, int here_doc);
void	exec_command_child(t_pipeline *pipe_data, int i, int here_doc);
int		create_pipes(int ***pipes, int n);
int		wait_for_children(pid_t last_pid, int cmd_count);
void	free_pipeline(t_pipeline *pipeline);

#endif