#ifndef PIPEX_H
# define PIPEX_H

# include "../pipex.h"
# include <sys/types.h>
# include <unistd.h>

typedef struct s_exec
{
	char	**args;
	char	*path;
	int		permission;
}			t_exec;

typedef struct s_pipeline
{
    t_exec			*commands;
    int				**pipes;
    int				infile_fd;
    int				outfile_fd;
    int				cmd_count;
    char *const		*envp;
}					t_pipeline;

void	open_in_out_files(t_pipeline *pipeline, char const *infile,
            char const *outfile, int here_doc);
void	setup_pipeline(t_pipeline *pipeline, char const *argv[],
            char const *envp[], int here_doc);
void	setup_here_doc(char const *limitter);

#endif
