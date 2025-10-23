/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:58 by akivam            #+#    #+#             */
/*   Updated: 2025/10/23 15:02:53 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf/printf.h"
#include "./get-next-line/get_next_line_bonus.h"
#include "libft.h"
#include "parser.h"
#include "pipex.h"
#include "pipex_utils.h"
#include <fcntl.h>
#include <unistd.h>

int	is_here_doc(char const *arg)
{
	return (ft_strncmp(arg, "here_doc", 8) == 0);
}

static void	initialize_pipeline(t_pipeline *pipeline, int argc,
		char const *argv[], char const *envp[])
{
	int	here_doc;
	int	ret;

	pipeline->commands = NULL;
	pipeline->pipes = NULL;
	pipeline->infile_fd = -1;
	pipeline->outfile_fd = -1;
	here_doc = is_here_doc(argv[1]);
	pipeline->cmd_count = argc - 3 - here_doc;
	pipeline->envp = (char *const *)envp;
	if (here_doc)
		setup_here_doc(argv[2]);
	ret = open_in_out_files(pipeline, argv[1], argv[argc - 1], here_doc);
	if (ret != 0)
	{
		free_pipeline(pipeline);
		ft_err_printf("Error: Failed to open files. Exiting.\n");
		exit(EXIT_FAILURE);
	}
	setup_pipeline(pipeline, argv, envp, here_doc);
	if (create_pipes(&pipeline->pipes, pipeline->cmd_count - 1) != 0)
	{
		free_pipeline(pipeline);
		exit(1);
	}
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
	initialize_pipeline(&pipeline, argc, argv, envp);
	here_doc = is_here_doc(argv[1]);
	last_pid = spawn_all_children(&pipeline, here_doc);
	exit_status = wait_for_children(last_pid, pipeline.cmd_count);
	free_pipeline(&pipeline);
	return (exit_status);
}
