#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_exec
{
	char		**args;
	char		*path;
}				t_exec;

typedef struct s_commands
{
	char		**paths;
	t_exec	cmd1;
	t_exec	cmd2;
}				t_commands;

typedef struct s_files
{
	int			infile;
	int			outfile;
}				t_files;

#endif