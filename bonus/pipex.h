/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:45 by akivam            #+#    #+#             */
/*   Updated: 2025/10/22 13:00:01 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <unistd.h>

typedef struct s_exec
{
	char		**args;
	char		*path;
	int			permission;
}				t_exec;

typedef struct s_pipeline
{
	t_exec		*commands;
	int			**pipes;
	int			infile_fd;
	int			outfile_fd;
	int			cmd_count;
	char *const	*envp;
}				t_pipeline;

int		open_in_out_files(t_pipeline *pipeline, char const *infile,
				char const *outfile, int here_doc);
int		setup_pipeline(t_pipeline *pipeline, char const *argv[],
				char const *envp[], int here_doc);
void		setup_here_doc(char const *limitter);

#endif
