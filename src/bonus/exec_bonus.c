/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:09:22 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/03 12:13:09 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	infile_cmd(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;
	int		j;

	j = -1;
	cmd_args = ft_split(var->av[i + 2], ' ');
	dup2(var->file1, STDIN_FILENO);
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pipefd, var);
	if (execve(var->cmds, cmd_args, NULL) == FAIL)
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
	int		j;

	cmd_args = ft_split(var->av[i + 2], ' ');
	j = -1;
	dup2(pipefd[i][0], STDIN_FILENO);
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	close_pipes(pipefd, var);
	if (execve(var->cmds, cmd_args, NULL) == FAIL)
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
	int		j;

	j = -1;
	cmd_args = ft_split(var->av[i + 2], ' ');
	dup2(var->file2, STDOUT_FILENO);
	dup2(pipefd[i][0], STDIN_FILENO);
	close_pipes(pipefd, var);
	if (execve(var->cmds, cmd_args, NULL) == FAIL)
	{
		perror("Execve failed:");
		return (free_arg(cmd_args));
	}
	free_arg(cmd_args);
	return (1);
}

void	proceed_pipes(t_var *var, int **pipefd, int i)
{
	if (i == 0)
	{
		if (open_files(var, i) == FAIL)
			return ;
		if (get_cmds(var, i) == FAIL)
			return ;
		infile_cmd(var, pipefd, i);
		close(var->file1);
	}
	else if (i == var->size - 2)
	{
		if (open_files(var, i) == FAIL)
			return ;
		if (get_cmds(var, i) == FAIL)
			return ;
		outfile_cmd(var, pipefd, i);
		close(var->file2);
	}
	else
	{
		if (get_cmds(var, i) == FAIL)
			return ;
		in_between_cmds(var, pipefd, i);
	}
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
			proceed_pipes(var, pipefd, i);
			break ;
		}
	}
	close_pipes(pipefd, var);
	i = -1;
	while (++i < var->size - 2)
		waitpid(pids[i], &status, 0);
	return (1);
}
