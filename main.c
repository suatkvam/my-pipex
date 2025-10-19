#include "libft.h"
#include "parser.h"
#include "printf.h"
#include "unistd.h"
#include "pipex.h"

int	main(int argc, char const *argv[], char const *envp[])
{
    t_commands pipex;

    if (argc != 5)
    {
        ft_printf("Error: Invalid number of arguments.\n");
        ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
        ft_printf("Example: %s file1 \"ls -l\" \"wc -l\" file2\n", argv[0]);
        exit(1);
    }
    pipex.paths = paths_formatter(envp);
    pipex.cmd1.args = ft_split(argv[2], ' ');
    pipex.cmd2.args = ft_split(argv[3], ' ');
    pipex.cmd1.path = find_command(pipex.paths, pipex.cmd1.args[0]);
    pipex.cmd2.path = find_command(pipex.paths, pipex.cmd2.args[0]);
    free_path(pipex.paths);
    free_path(pipex.cmd1.args);
    free_path(pipex.cmd2.args);
    if (pipex.cmd1.path)
        free(pipex.cmd1.path);
    if (pipex.cmd2.path)
        free(pipex.cmd2.path);
    return (0);
}
