/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:47:20 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/03 12:14:16 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	close_pipes(int **pipefd, t_var *var)
{
	int	j;

	j = -1;
	while (++j < var->size)
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

int	check_access(t_var *var, int i)
{
	if (var->cmds == 0)
		return (0);
	if (access(var->cmds, X_OK) == -1 && var->path[i + 1] == 0)
		return (0);
	else if (access(var->cmds, X_OK) == 0)
		return (1);
	return (-1);
}

int	cmd_not_found(t_var *var, int k, char **cmd_args)
{
	write (2, var->av[k + 2], ft_strlen(var->av[k + 2]));
	write (2, ": command not found\n", 20);
	free(var->cmds);
	return (free_arg(cmd_args));
}

int	no_such_file(t_var *var, int k, char **cmd_args)
{
	write (2, var->av[k + 2], ft_strlen(var->av[k + 2]));
	write (2, ": No such file or directory\n", 28);
	free(var->cmds);
	return (free_arg(cmd_args));
}

int	get_cmds(t_var *var, int k)
{
	int		i;
	char	**cmd_args;

	i = -1;
	if (var->av[k + 2][0] == '/')
	{
		cmd_args = ft_split(var->av[k + 2], ' ');
		var->cmds = *cmd_args;
		if (check_access(var, -1) == SUCCESS)
			return (free_arg(cmd_args) + 1);
		else
			return (no_such_file(var, k, cmd_args));
	}
	while (var->path[++i])
	{
		cmd_args = ft_split(var->av[k + 2], ' ');
		var->cmds = ft_strjoin(var->path[i], *cmd_args);
		if (check_access(var, i) == SUCCESS)
			break ;
		else if (check_access(var, i) == FAIL)
			return (cmd_not_found(var, k, cmd_args));
		free(var->cmds);
		free_arg(cmd_args);
	}
	return (free_arg(cmd_args) + 1);
}
