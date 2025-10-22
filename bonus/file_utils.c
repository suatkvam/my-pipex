/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:09 by akivam            #+#    #+#             */
/*   Updated: 2025/10/22 22:37:06 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/printf.h"
#include "parser.h"
#include "pipex.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int	open_here_doc_files(t_pipeline *pipeline, char const *outfile)
{
	pipeline->infile_fd = open(".here_doc_temp", O_RDONLY);
	if (pipeline->infile_fd < 0)
	{
		ft_err_printf("Error: Could not open temporary here_doc file.\n");
		return (-1);
	}
	if (unlink(".here_doc_temp") != 0)
		ft_err_printf("Warning: failed to unlink .here_doc_temp\n");
	pipeline->outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (0);
}

static int	open_regular_files(t_pipeline *pipeline, char const *infile,
		char const *outfile)
{
	pipeline->infile_fd = open_file(infile, O_RDONLY, 0);
	pipeline->outfile_fd = open_file(outfile, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	return (0);
}

int	open_in_out_files(t_pipeline *pipeline, char const *infile,
		char const *outfile, int here_doc)
{
	int	ret;

	if (here_doc)
		ret = open_here_doc_files(pipeline, outfile);
	else
		ret = open_regular_files(pipeline, infile, outfile);
	if (ret != 0)
		return (-1);
	if (pipeline->infile_fd < 0)
	{
		ft_err_printf("Warning: Could not open input file.\
			 Child will handle it.\n");
	}
	if (pipeline->outfile_fd < 0)
	{
		ft_err_printf("Error: Could not open output file '%s' (errno=%d: %s)\n",
			outfile, errno, strerror(errno));
		return (-1);
	}
	return (0);
}
