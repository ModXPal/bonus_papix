/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <rcollas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 14:17:08 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/18 15:41:47 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_pipefd(t_var *var, int ***pipefd)
{
	int	i;

	i = -1;
	*pipefd = malloc(sizeof(int *) * (var->size));
	if (*pipefd == FAIL)
		return (0);
	while (++i < var->size)
	{
		(*pipefd)[i] = malloc(sizeof(int) * 2);
		if ((*pipefd)[i] == FAIL)
			return (0);
	}
	i = -1;
	while (++i < var->size)
	{
		if (pipe((*pipefd)[i]) == -1)
			return (0);
	}
	return (1);
}

int	init_pid(pid_t	**pids, t_var *var)
{
	*pids = (pid_t *)malloc(sizeof(pid_t) * (var->size - 1));
	if (*pids == FAIL)
	{
		free(*pids);
		return (0);
	}
	return (1);
}

void	init_var(t_var *var, char **av, char **env, int ac)
{
	var->av = av;
	var->ac = ac;
	var->size = ac - 2;
	var->env = env;
	var->cmds = NULL;
}
