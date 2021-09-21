/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:47:20 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/21 23:49:29 by rcollas          ###   ########.fr       */
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

int	get_cmds(t_var *var)
{
	int	i;
	int	j;
	int	k;
	char	**cmd_args;

	j = 0;
	k = 2;
	var->cmds = (char **)malloc(sizeof(char *) * (var->size + 1));
	while (k + 1 < var->size)
	{
		i = -1;
		while (var->path[++i])
		{
			cmd_args = ft_split(var->av[k], ' ');
			var->cmds[j] = ft_strjoin(var->path[i], *cmd_args);
			if (access(var->cmds[j], X_OK) == 0)
				break ;
			if (var->path[i + 1])
				free(var->cmds[j]);
			free_arg(cmd_args);
		}
		free_arg(cmd_args);
		j++;
		k++;
	}
	var->cmds[j] = NULL;
	return (1);
}

int	free_arg(char **cmd_args)
{
	int	i;

	i = -1;
	while (cmd_args[++i])
		free(cmd_args[i]);
	free(cmd_args);
	return (0);
}
