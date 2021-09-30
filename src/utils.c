/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:47:20 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/30 11:38:04 by rcollas          ###   ########.fr       */
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

int	check_access(t_var *var, int k, int i)
{
	if (access(var->cmds[k], X_OK) == -1 && var->path[i + 1] == 0)
		return (0);
	else if (access(var->cmds[k], X_OK) == 0)
		return (1);
	return (-1);
}

int	get_cmds(t_var *var)
{
	int		i;
	int		k;
	char	**cmd_args;

	k = -1;
	var->cmds = (char **)malloc(sizeof(char *) * (var->size + 1));
	while (++k < var->size - 1)
	{
		i = -1;
		while (var->path[++i])
		{
			cmd_args = ft_split(var->av[k + 2], ' ');
			var->cmds[k] = ft_strjoin(var->path[i], *cmd_args);
			if (check_access(var, k, i) == SUCCESS)
				break ;
			else if (check_access(var, k, i) == FAIL)
			{
				write (2, var->av[k + 2], ft_strlen(var->av[k + 2]));
				write (2, ": command not found\n", 21);
				return (free_arg(cmd_args));
			}
			free(var->cmds[k]);
			free_arg(cmd_args);
		}
		free_arg(cmd_args);
	}
	var->cmds[k] = NULL;
	return (1);
}
