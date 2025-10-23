/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:21 by akivam            #+#    #+#             */
/*   Updated: 2025/10/23 14:32:58 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/printf.h"
#include "pipex.h"
#include "unistd.h"
#include <stdlib.h>

int	create_pipes(int ***pipes, int n)
{
	int	i;

	*pipes = malloc(sizeof(int *) * n);
	if (!*pipes)
	{
		ft_err_printf("Error: memory allocation failed for pipes.\n");
		return (1);
	}
	i = 0;
	while (i < n)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
		{
			ft_err_printf("Error: memory allocation failed for pipe.\n");
			return (1);
		}
		if (pipe((*pipes)[i]) == -1)
		{
			ft_err_printf("Error: pipe creation failed.\n");
			return (1);
		}
		i++;
	}
	return (0);
}
