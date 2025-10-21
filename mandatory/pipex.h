/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akivam <akivam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:50:11 by akivam            #+#    #+#             */
/*   Updated: 2025/10/21 18:50:12 by akivam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_exec
{
	char	**args;
	char	*path;
	int		permission;
}			t_exec;

typedef struct s_pipeline	t_pipeline;

#endif