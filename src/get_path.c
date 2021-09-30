/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <rcollas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:44:32 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/30 11:45:10 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	add_slash(t_var *var)
{
	int		i;
	char	*to_free;

	i = -1;
	while (var->path[++i])
	{
		to_free = var->path[i];
		var->path[i] = ft_strjoin(var->path[i], "/");
		free(to_free);
	}
}

int	get_path_line(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (0);
}

char	**get_binaries_path(char **env)
{
	int	line;

	if (!get_path_line(env))
		return (0);
	line = get_path_line(env);
	return (ft_split(*(env + line), ':'));
}
