#include "libft.h"
#include "parser.h"
#include "printf.h"
#include "stdlib.h"
#include "unistd.h"

char	*find_command(char **paths, const char *cmd)
{
	char	*full_path;
	size_t	len;
	int		i;

	full_path = NULL;
	i = 0;
	if (!paths || !cmd)
		return (NULL);
	while (paths[i])
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
		free(full_path);
		i++;
	}
	return (NULL);
}
