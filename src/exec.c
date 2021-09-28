/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:09:22 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/27 08:28:33 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	infile_cmd(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;

	cmd_args = ft_split(var->av[i + 2], ' ');
	dup2(var->file1, STDIN_FILENO);
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	if (close(var->file1) == -1)
	{
		perror("Close start failed");
		return (free_arg(cmd_args));
	}
	if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
	{
		perror("Execve failed:");
		return (free_arg(cmd_args));
	}
	free_arg(cmd_args);
	return (1);
}

int	in_between_cmds(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;

	cmd_args = ft_split(var->av[i + 2], ' ');
	dup2(pipefd[i][0], STDIN_FILENO);
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	if (close(pipefd[i][1]))
	{
		perror("Close start failed");
		return (free_arg(cmd_args));
	}
	if (close(var->file2))
	{
		perror("Close start failed");
		return (free_arg(cmd_args));
	}
	if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
	{
		perror("Execve failed:");
		return (free_arg(cmd_args));
	}
	free_arg(cmd_args);
	return (1);
}

int	outfile_cmd(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;

	cmd_args = ft_split(var->av[i + 2], ' ');
	dup2(var->file2, STDOUT_FILENO);
	dup2(pipefd[i][0], STDIN_FILENO);
	if (close(pipefd[i][1]))
	{
		perror("Close start failed");
		return (free_arg(cmd_args));
	}
	if (close(pipefd[i + 1][0]))
	{
		perror("Close start failed");
		return (free_arg(cmd_args));
	}
	if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
	{
		perror("Execve failed:");
		return (free_arg(cmd_args));
	}
	free_arg(cmd_args);
	return (1);
}

int	proceed_pipes(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;

	cmd_args = ft_split(var->av[i + 2], ' ');
	if (i == 0)
		infile_cmd(var, pipefd, i);
	else if (i == var->size - 2)
		outfile_cmd(var, pipefd, i);
	else
		in_between_cmds(var, pipefd, i);
	return (1);
}

int	exec(t_var *var, int **pipefd, pid_t *pids)
{
	int		i;
	int		status;

	i = -1;
	while (++i < var->size - 1)
	{
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
		}
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
	i = -1;
	while (++i < var->size - 1)
		waitpid(pids[i], &status, 0);
	return (1);
}
