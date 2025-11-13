/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:00 by akivam            #+#    #+#             */
/*   Updated: 2025/11/13 17:04:33 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/printf.h"
#include <fcntl.h>
#include "libft.h"
#include "parser.h"
#include "pipex.h"
#include "pipex_utils.h"
#include <unistd.h>

int	open_in_out_files(t_pipeline *pipeline, char const *infile,
		char const *outfile)
{
	pipeline->infile_fd = open_file(infile, O_RDONLY, 0);
	pipeline->outfile_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (pipeline->infile_fd < 0)
	{
		ft_err_printf("Warning: Could not open input file. Child \
			will handle it.\n");
	}
	if (pipeline->outfile_fd < 0)
	{
		ft_err_printf("Error: Could not open output file.\n");
		return (-1);
	}
	return (0);
}

void	setup_commands(t_pipeline *pipeline, char const *argv[],
		char const *envp[])
{
	char	**paths;
	int		perm_denied;

	paths = paths_formatter(envp);
	pipeline->commands = malloc(sizeof(t_exec) * pipeline->cmd_count);
	if (!pipeline->commands)
	{
		ft_err_printf("Error: Memory allocation failed.\n");
		exit(1);
	}
	pipeline->commands[0].args = ft_split(argv[2], ' ');
	pipeline->commands[1].args = ft_split(argv[3], ' ');
	pipeline->commands[0].path = find_command(paths,
			pipeline->commands[0].args[0], &perm_denied);
	pipeline->commands[0].permission = perm_denied;
	pipeline->commands[1].path = find_command(paths,
			pipeline->commands[1].args[0], &perm_denied);
	pipeline->commands[1].permission = perm_denied;
	free_path(paths);
}

static void	init_pipeline(t_pipeline *pipeline, int argc, char const *argv[],
		char const *envp[])
{
	pipeline->commands = NULL;
	pipeline->pipes = NULL;
	pipeline->infile_fd = -1;
	pipeline->outfile_fd = -1;
	if (argc != 5)
	{
		ft_err_printf("Error: Invalid number of arguments.\n");
		ft_printf("Usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		ft_printf("Example: %s file1 \"ls -l\" \"wc -l\" file2\n", argv[0]);
		exit(1);
	}
	pipeline->cmd_count = 2;
	pipeline->envp = (char *const *)envp;
}

int	main(int argc, char const *argv[], char const *envp[])
{
	t_pipeline	pipeline;
	pid_t		last_pid;
	int			exit_status;

	init_pipeline(&pipeline, argc, argv, envp);
	if (open_in_out_files(&pipeline, argv[1], argv[4]) != 0)
	{
		if (pipeline.infile_fd >= 0)
			close(pipeline.infile_fd);
		if (pipeline.outfile_fd >= 0)
			close(pipeline.outfile_fd);
		free_pipeline(&pipeline);
		exit(EXIT_FAILURE);
	}
	setup_commands(&pipeline, argv, envp);
	if (create_pipes(&pipeline.pipes, pipeline.cmd_count - 1) != 0)
	{
		free_pipeline(&pipeline);
		exit(EXIT_FAILURE);
	}
	last_pid = spawn_all_children(&pipeline);
	exit_status = wait_for_children(last_pid, pipeline.cmd_count);
	free_pipeline(&pipeline);
	return (exit_status);
}
