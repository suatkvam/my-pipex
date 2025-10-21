/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:51:28 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 18:51:29 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

char	**paths_formatter(char const *envp[]);
void	free_path(char **path);
char	*find_command(char **paths, const char *cmd, int *permission_denied);
int		open_file(const char *file_name, int flags, int mode);
#endif
