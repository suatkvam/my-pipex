#ifndef PARSER_H
# define PARSER_H

char	**paths_formatter(char const *envp[]);
void	free_path(char **path);
char	*find_command(char **paths, const char *cmd, int *permission_denied);
int		open_file(const char *file_name, int flags, int mode);
#endif
