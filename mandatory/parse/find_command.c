/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:38 by akivam            #+#    #+#             */
/*   Updated: 2025/10/23 14:31:55 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include <stdlib.h>
#include <unistd.h>

static char	*find_command_in_paths(char **paths, const char *cmd,
		int *permission_denied)
{
	char	*full_path;
	size_t	len;
	int		i;

	i = -1;
	while (paths && paths[++i])
	{
		len = ft_strlen(paths[i]) + 1 + ft_strlen(cmd) + 1;
		full_path = malloc(len);
		if (!full_path)
			return (NULL);
		ft_strlcpy(full_path, paths[i], len);
		ft_strlcat(full_path, "/", len);
		ft_strlcat(full_path, cmd, len);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		else if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == -1)
		{
			free(full_path);
			*permission_denied = 1;
			return (NULL);
		}
		free(full_path);
	}
	return (NULL);
}

char	*find_command(char **paths, const char *cmd, int *permission_denied)
{
	*permission_denied = 0;
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
		{
			*permission_denied = 1;
			return (NULL);
		}
		return (NULL);
	}
	if (!paths)
		return (NULL);
	return (find_command_in_paths(paths, cmd, permission_denied));
}
