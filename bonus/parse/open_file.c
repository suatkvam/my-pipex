/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:31 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 18:51:32 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>

int	open_file(const char *file_name, int flags, int mode)
{
	int	fd;

	fd = open(file_name, flags, mode);
	if (fd < 0)
		return (-1);
	return (fd);
}
