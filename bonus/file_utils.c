/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:09 by akivam            #+#    #+#             */
/*   Updated: 2025/10/22 12:59:13 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/printf.h"
#include "parser.h"
#include "pipex.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	open_in_out_files(t_pipeline *pipeline, char const *infile,
		char const *outfile, int here_doc)
{
	if (here_doc)
	{
		pipeline->infile_fd = open(".here_doc_temp", O_RDONLY);
		if (pipeline->infile_fd < 0)
		{
			ft_err_printf("Error: Could not open temporary here_doc file.\n");
			return (-1);
		}
		if (unlink(".here_doc_temp") != 0)
			ft_err_printf("Warning: failed to unlink .here_doc_temp\n");
		pipeline->outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	else
	{
		pipeline->infile_fd = open_file(infile, O_RDONLY, 0);
		pipeline->outfile_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	}
	if (pipeline->infile_fd < 0)
	{
		ft_err_printf("Error: Could not open input file.\n");
		return (-1);
	}
	if (pipeline->outfile_fd < 0)
	{
		ft_err_printf("Error: Could not open output file.\n");
		return (-1);
	}
	return (0);
}
