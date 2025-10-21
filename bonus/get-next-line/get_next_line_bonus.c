/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:02:50 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 18:03:32 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

static char	*extract_line(char *stash)
{
	char	*newline;
	size_t	i;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (newline)
		i = (newline - stash) + 1;
	else
		i = ft_strlen(stash);
	return (ft_substr(stash, 0, i));
}

static char	*update_stash(char *stash)
{
	char	*new_stash;
	char	*new_line;

	if (!stash)
		return (NULL);
	new_line = ft_strchr(stash, '\n');
	if (!new_line)
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strdup(new_line + 1);
	free(stash);
	return (new_stash);
}

static char	*read_line(int fd, char *stash)
{
	char	*buffer;
	ssize_t	read_byte;

	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	while (!stash || !ft_strchr(stash, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (read_byte == 0)
			break ;
		buffer[read_byte] = '\0';
		stash = gnl_ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;
	int			i;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
	{
		i = 0;
		while (i < 1024)
		{
			if (stash[i])
			{
				free(stash[i]);
				stash[i] = NULL;
			}
			i++;
		}
		return (NULL);
	}
	stash[fd] = read_line(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
