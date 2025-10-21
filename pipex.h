#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_exec
{
	char	**args;
	char	*path;
	int		permission;
}			t_exec;

typedef struct s_pipeline	t_pipeline;

#endif