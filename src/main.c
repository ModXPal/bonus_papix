/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:01:54 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/30 11:34:53 by rcollas          ###   ########.fr       */
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
	while (++i < var->size + 1)
	{
		(*pipefd)[i] = malloc(sizeof(int) * 2);
		if ((*pipefd)[i] == FAIL)
			return (0);
	}
	i = -1;
	while (++i < var->size + 1)
	{
		if (pipe((*pipefd)[i]) == -1)
			return (0);
	}
	return (1);
}

int	init_pid(pid_t	**pids, t_var *var)
{
	*pids = (pid_t *)malloc(sizeof(pid_t) * (var->size + 1));
	if (*pids == FAIL)
	{
		free(*pids);
		return (0);
	}
	return (1);
}

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
	var->av = av;
	var->size = ac - 2;
	var->env = env;
	var->file1 = open(av[1], O_RDONLY);
	var->file2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
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
	free_arg(var->path);
	free_arg(var->cmds);
	free(var->pids);
}
