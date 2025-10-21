/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:18 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 18:51:19 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_utils.h"
#include "stdlib.h"
#include "parser.h"

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline || !pipeline->commands)
		return ;
	i = 0;
	while (i < pipeline->cmd_count)
	{
		free_path(pipeline->commands[i].args);
		if (pipeline->commands[i].path)
			free(pipeline->commands[i].path);
		i++;
	}
	free(pipeline->commands);
	if (pipeline->pipes)
	{
		i = 0;
		while (i < pipeline->cmd_count - 1)
		{
			free(pipeline->pipes[i]);
			i++;
		}
		free(pipeline->pipes);
	}
}
