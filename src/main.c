/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:01:54 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/26 17:43:48 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	proceed_pipes(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;

	cmd_args = ft_split(var->av[i + 2], ' ');
	if (i == 0)
	{
		//printf("cmd = %s\n", var->cmds[i]);
		//printf("cmd_args = %s\n", *cmd_args);
		dup2(var->file1, STDIN_FILENO);
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
		//close(pipefd[i + 1][0]);
		//close(pipefd[i + 1][1]);
		if (close(var->file1) == -1)
		{
			perror("Close start failed");
			return (0);
		}
		if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
		{
			perror("Execve failed:");
			return (0);
		}
	}
	else if (i == var->size - 2)
	{
		//printf("cmd 2 = %s\n", var->cmds[i]);
		//printf("cmd_args 2 = %s\n", *cmd_args);
		dup2(var->file2, STDOUT_FILENO);
		dup2(pipefd[i][0], STDIN_FILENO);
		if (close(pipefd[i][1]))
		{
			perror("Close start failed");
			return (0);
		}
		if (close(var->file2))
		{
			perror("Close start failed");
			return (0);
		}
		if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
		{
			perror("Execve failed:");
			return (0);
		}
	}
	else
	{
		//printf("cmd sup = %s\n", var->cmds[i]);
		//printf("cmd_args sup = %s\n", *cmd_args);
		dup2(pipefd[i][0], STDIN_FILENO);
		dup2(pipefd[i + 1][1], STDOUT_FILENO);
		if (close(pipefd[i][1]))
		{
			perror("Close start failed");
			return (0);
		}
		if (close(pipefd[i + 1][0]))
		{
			perror("Close start failed");
			return (0);
		}
		if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
		{
			perror("Execve failed:");
			return (0);
		}
	}
	return (1);
}

int	init_pipefd(t_var *var, int ***pipefd)
{
	int	i;

	i = -1;
	*pipefd = malloc(sizeof(int *) * (var->size + 1));
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

int	pipex(t_var *var)
{
	int	**pipefd;
	int	status;
	pid_t	pids[var->size + 1];
	int	i;
	int	j;

	i = -1;
	j = -1;
	pipefd = NULL;
	if (init_pipefd(var, &pipefd) == FAIL)
	{
		perror("Pipe allocation failed");
		return (0);
	}
	while  (++i < var->size - 1)
	{
		j = -1;
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("Fork failed:");
			return (0);
		}
		if (pids[i] == 0)
		{
			if (proceed_pipes(var, pipefd, i) == FAIL)
				return (0);
			return (1);
		}
		/*
		while (++j < var->size + 1)
		{
			if (j != i)
			{
				printf("close pipefd[%d][0]\n", j);
				if (close(pipefd[j][0]) == -1)
				{
					perror("Close failed 1");
					return (0);
				}
			}
			if (i + 1 != j)
			{
				printf("close pipefd[%d][1]\n", j);
				if (close(pipefd[j][1]) == -1)
				{
					perror("Close failed 2");
					return (0);
				}
			}
		}
		*/
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	i = -1;
	while (++i < var->size)
		waitpid(pids[i], &status, 0);
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
	var->size = ac - 2;
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
