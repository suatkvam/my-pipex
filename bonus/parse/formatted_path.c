#include "libft.h"

static char	*get_paths(char const *envp[])
{
	int	i;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strdup(envp[i] + 5));
		++i;
	}
	return (NULL);
}

char	**paths_formatter(char const *envp[])
{
	char	**splited_path;
	char	*path;

	path = get_paths(envp);
	if (!path)
		return (NULL);
	splited_path = ft_split(path, ':');
	free(path);
	return (splited_path);
}
