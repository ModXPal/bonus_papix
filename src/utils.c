/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:47:20 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/30 12:02:18 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	close_pipes(int **pipefd, t_var *var)
{
	int	j;

	j = -1;
	while (++j < var->size + 1)
	{
		if (close(pipefd[j][0]) == -1)
		{
			perror("Failed to close pipe");
			return (0);
		}
		if (close(pipefd[j][1]) == -1)
		{
			perror("Failed to close pipe");
			return (0);
		}
	}
	return (1);
}

int	check_access(t_var *var, int k, int i)
{
	if (var->cmds[k] == 0)
		return (0);
	if (access(var->cmds[k], X_OK) == -1 && var->path[i + 1] == 0)
		return (0);
	else if (access(var->cmds[k], X_OK) == 0)
		return (1);
	return (-1);
}

int	cmd_not_found(t_var *var, int k, char **cmd_args)
{
	write (2, var->av[k + 2], ft_strlen(var->av[k + 2]));
	write (2, ": command not found\n", 21);
	return (free_arg(cmd_args));
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
				return (cmd_not_found(var, k, cmd_args));
			free(var->cmds[k]);
			free_arg(cmd_args);
		}
		free_arg(cmd_args);
	}
	var->cmds[k] = NULL;
	return (1);
}
