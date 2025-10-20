#ifndef PIPEX_UTILS_H
# define PIPEX_UTILS_H

# include "../pipex.h"

typedef struct s_pipeline
{
	t_exec	*commands;
	int		**pipes;
	int		infile_fd;
	int		outfile_fd;
	int		cmd_count;
	char *const *envp;
}			t_pipeline;

int			create_pipes(int ***pipes, int n);
void		exec_command_child(t_pipeline *pipe_data, int i);
void		spawn_all_children(t_pipeline *pipe_data);
int			manage_pipeline(t_pipeline *pipe_data);

#endif