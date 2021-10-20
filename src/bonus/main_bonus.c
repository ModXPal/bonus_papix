/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:01:54 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/20 10:53:41 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	pipex(t_var *var)
{
	int		**pipefd;

	pipefd = NULL;
	if (init_pid(&var->pids, var) == FAIL)
	{
		perror("Pid allocation failed");
		return (0);
	}
	if (init_pipefd(var, &pipefd) == FAIL)
	{
		if (*pipefd)
			free_pipes(pipefd, var);
		free(var->pids);
		perror("Pipe allocation failed");
		return (0);
	}
	exec(var, pipefd, var->pids);
	free_pipes(pipefd, var);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	t_var	var[1];

	if (ac < 5)
	{
		ft_putstr_fd("Check arguments\n", 2);
		return (0);
	}
	init_var(var, av, env, ac);
	var->path = get_binaries_path(env);
	if (var->path == FAIL)
		return (0);
	add_slash(var);
	if (pipex(var) == FAIL)
		return (free_arg(var->path));
	free(var->pids);
	return (free_arg(var->path));
}
