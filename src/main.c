/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:01:54 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/30 14:20:28 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
		ft_putstr_fd("Missing arguments\n", 0);
		return (0);
	}
	init_var(var, av, env, ac);
	if (var->file1 < 0)
	{
		perror(av[1]);
		return (0);
	}
	if (var->file2 < 0)
	{
		perror(av[var->size + 1]);
		return (0);
	}
	var->path = get_binaries_path(env);
	add_slash(var);
	if (get_cmds(var) == FAIL)
		return (free_arg(var->path) + free_arg(var->cmds));
	pipex(var);
	free(var->pids);
	return (free_arg(var->path) + free_arg(var->cmds));
}
