/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:01:54 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/22 00:01:23 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	proceed_pipes(t_var *var, int end[2], int i)
{
	char	**cmd_args;

	cmd_args = ft_split(var->av[i + 2], ' ');
	printf("cmd = %s\n", var->cmds[i]);
	printf("cmd_args = %s\n", *cmd_args);
	if (i == 0)
	{
		printf("cmd = %s\n", var->cmds[i]);
		printf("cmd_args = %s\n", *cmd_args);
		dup2(var->file1, STDIN_FILENO);
		dup2(end[1], STDOUT_FILENO);
		close(end[0]);
		close(var->file1);
		if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
			return (0);
	}
	else if (i == var->size - 2)
	{
		printf("cmd = %s\n", var->cmds[i]);
		printf("cmd_args = %s\n", *cmd_args);
		dup2(var->file2, STDOUT_FILENO);
		dup2(end[0], STDIN_FILENO);
		close(end[1]);
		close(var->file2);
		if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
			return (0);
	}
	return (1);
}

int	pipex(t_var *var)
{
	int	end[2];
	int	status;
	int	pid;
	int	i;

	i = -1;
	while  (++i < var->size - 3)
	{
		pid = fork();
		pipe(end);
		if (pid == 0)
		{
			printf("i = %d\n", i);
			proceed_pipes(var, end, i);
		}
		//close(end[0]);
		//close(end[1]);
		waitpid(pid, &status, 0);
	}
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
	var->path = get_binaries_path(env);
	var->av = av;
	var->size = ac;
	var->env = env;
	add_slash(var);
	get_cmds(var);
	var->file1 = open(av[1], O_RDONLY);
	var->file2 = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (var->file1 < 0 || var->file2 < 0)
	{
		perror(av[1]);
		return (0);
	}
	pipex(var);
	free_arg(var->path);
	free_arg(var->cmds);
}
