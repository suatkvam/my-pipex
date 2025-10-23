/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:30 by akivam            #+#    #+#             */
/*   Updated: 2025/10/23 14:32:03 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

int	open_file(const char *file_name, int flags, int mode)
{
	int	fd;

	fd = open(file_name, flags, mode);
	if (fd < 0)
		return (-1);
	return (fd);
}
