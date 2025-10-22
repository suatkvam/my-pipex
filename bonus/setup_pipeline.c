/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:42 by akivam            #+#    #+#             */
/*   Updated: 2025/10/22 12:58:18 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/printf.h"
#include "libft.h"
#include "parser.h"
#include "pipex.h"
#include <stdlib.h>

int	setup_pipeline(t_pipeline *pipeline, char const *argv[], char const *envp[],
		int here_doc)
{
	char	**paths;
	int		permision;
	int		i;

	paths = paths_formatter(envp);
	pipeline->commands = malloc(sizeof(t_exec) * pipeline->cmd_count);
	if (!pipeline->commands)
	{
		ft_err_printf("Error: Memory allocation failed.\n");
		free_path(paths);
		return (-1);
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
	return (0);
}
