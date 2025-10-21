#include "./ft_printf/printf.h"
#include "./get-next-line/get_next_line_bonus.h"
#include "fcntl.h"
#include "libft.h"
#include "parser.h"
#include "pipex.h"
#include "pipex_utils.h"
#include "unistd.h"

int	is_here_doc(char const *arg)
{
	return (ft_strncmp(arg, "here_doc", 8) == 0);
	// buraya "<<" ekelenebilir sonuçta fork var
}

void	open_in_out_files(t_pipeline *pipeline, char const *infile,
		char const *outfile, int here_doc)
{
	if (here_doc)
	{
		pipeline->infile_fd = open(".here_doc_tmp", O_RDONLY);
		pipeline->outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND,
				0644); // O_APPEND kullanılıyor
	}
	else
	{
		pipeline->infile_fd = open_file(infile, O_RDONLY, 0);
		pipeline->outfile_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644); // O_TRUNC kullanılıyor
	}
	if (pipeline->infile_fd < 0)
		ft_err_printf("Error: Could not open input file.\n");
	if (pipeline->outfile_fd < 0)
	{
		ft_err_printf("Error: Could not open output file.\n");
		exit(EXIT_FAILURE);
	}
}

void	setup_pipeline(t_pipeline *pipeline, char const *argv[],
		char const *envp[], int here_doc)
{
	char	**paths;
	int		permision;
	int		i;

	paths = paths_formatter(envp);
	pipeline->commands = malloc(sizeof(t_exec) * pipeline->cmd_count);
	if (!pipeline->commands)
	{
		ft_err_printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	i = -1;
	while (++i < pipeline->cmd_count)
	{
		pipeline->commands[i].args = ft_split(argv[i + 2 + here_doc], ' ');
		pipeline->commands[i].path = find_command(paths,
				pipeline->commands[i].args[0], &permision);
		pipeline->commands[i].permission = permision;
	}
	free_path(paths);
}

void	setup_here_doc(char const *limitter)
{
	int		temp_fd;
	char	*line;

	temp_fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd < 0)
		exit(EXIT_FAILURE);
	ft_printf("pipex here_doc> ");
	while ((line = get_next_line(STDIN_FILENO)) != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		// Limitter ile karşılaştır
		if (ft_strncmp(line, limitter, ft_strlen(limitter) + 1) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		ft_putendl_fd(line, temp_fd);
		free(line);
		ft_printf("pipex here_doc> ");
	}
	close(temp_fd);
}

int	main(int argc, char const *argv[], char const *envp[])
{
	t_pipeline	pipeline;
	pid_t		last_pid;
	int			exit_status;
	int			here_doc;

	if (argc < 5)
	{
		ft_err_printf("Error: Invalid number of arguments.\n");
		ft_printf("Usage: %s infile cmd1 cmd2 ... outfile\n", argv[0]);
		ft_printf("       %s here_doc LIMITER cmd1 cmd2 ... outfile\n",
			argv[0]);
		exit(1);
	}
	here_doc = is_here_doc(argv[1]);
	pipeline.cmd_count = argc - 3 - here_doc;
	pipeline.envp = (char *const *)envp;
	if (here_doc)
		setup_here_doc(argv[2]);
	open_in_out_files(&pipeline, argv[1], argv[argc - 1], here_doc);
	setup_pipeline(&pipeline, argv, envp, here_doc);
	if (create_pipes(&pipeline.pipes, pipeline.cmd_count - 1) != 0)
	{
		free_pipeline(&pipeline);
		exit(1);
	}
	last_pid = spawn_all_children(&pipeline, here_doc);
	exit_status = wait_for_children(last_pid, pipeline.cmd_count);
	free_pipeline(&pipeline);
	if (here_doc)
		unlink(".here_doc_tmp");
	return (exit_status);
}
