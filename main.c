#include "./ft_printf/printf.h"
#include "fcntl.h"
#include "libft.h"
#include "parser.h"
#include "pipex.h"
#include "pipex_utils.h"
#include "unistd.h"

void	free_pipeline(t_pipeline *pipeline)
{
	if (!pipeline || !pipeline->commands)
		return ;
	for (int i = 0; i < pipeline->cmd_count; i++)
	{
		free_path(pipeline->commands[i].args);
		if (pipeline->commands[i].path)
			free(pipeline->commands[i].path);
	}
	free(pipeline->commands);
	if (pipeline->pipes)
	{
		for (int i = 0; i < pipeline->cmd_count - 1; i++)
			free(pipeline->pipes[i]);
		free(pipeline->pipes);
	}
}
int	main(int argc, char const *argv[], char const *envp[])
{
	t_pipeline	pipeline;
	char		**paths;

	if (argc != 5)
	{
		ft_err_printf("Error: Invalid number of arguments.\n");
		ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		ft_printf("Example: %s file1 \"ls -l\" \"wc -l\" file2\n", argv[0]);
		exit(1);
	}
	pipeline.cmd_count = 2;
	pipeline.envp = (char *const *)envp;
	pipeline.infile_fd = open_file(argv[1], O_RDONLY, 0);
	pipeline.outfile_fd = open_file(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (pipeline.infile_fd < 0 || pipeline.outfile_fd < 0)
	{
		ft_err_printf("Error: Could not open input/output file.\n");
		exit(1);
	}
	pipeline.commands = malloc(sizeof(t_exec) * pipeline.cmd_count);
	if (!pipeline.commands)
	{
		ft_err_printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	paths = paths_formatter(envp);
	pipeline.commands[0].args = ft_split(argv[2], ' ');
	pipeline.commands[1].args = ft_split(argv[3], ' ');
	pipeline.commands[0].path = find_command(paths,
			pipeline.commands[0].args[0]);
	pipeline.commands[1].path = find_command(paths,
			pipeline.commands[1].args[0]);
	free_path(paths);
	// --- PIPE OLUŞTURMA ---
	if (create_pipes(&pipeline.pipes, pipeline.cmd_count - 1) != 0)
	{
		free_pipeline(&pipeline);
		exit(1);
	}
	// ----------------------
	if (pipeline.commands[0].path)
		ft_printf("cmd1 path: %s\n", pipeline.commands[0].path); // debug
	if (pipeline.commands[1].path)
		ft_printf("cmd2 path: %s\n", pipeline.commands[1].path); // debug
	if (manage_pipeline(&pipeline) != 0)
	{
		ft_err_printf("Error: Pipeline execution failed.\n");
		free_pipeline(&pipeline);
		exit(1);
	}
	free_pipeline(&pipeline);
	return (0);
}
