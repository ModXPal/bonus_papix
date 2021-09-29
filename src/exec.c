/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 18:09:22 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/29 18:42:06 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	infile_cmd(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;
	int	j;

	j = -1;
	cmd_args = ft_split(var->av[i + 2], ' ');
	dup2(var->file1, STDIN_FILENO);
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	while (++j < var->size + 1)
	{
		if (close(pipefd[j][0]) == -1)
			perror("infile close 1");
		if (j != i + 1)
			if (close(pipefd[j][1]) == -1)
				perror("infile close 1");
	}
	//close(pipefd[0][0]);
	//close(pipefd[0][1]);
	//close(pipefd[i + 1][0]);
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
	close(pipefd[i + 1][1]);
	free_arg(cmd_args);
	return (1);
}

int	in_between_cmds(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;
	int	j;

	cmd_args = ft_split(var->av[i + 2], ' ');
	j = -1;
	dup2(pipefd[i][0], STDIN_FILENO);
	dup2(pipefd[i + 1][1], STDOUT_FILENO);
	while (++j < var->size + 1)
	{
		if (j != i)
		{
			if (close(pipefd[j][0]) == -1)
				perror("in between close");
		}
		if (j != i + 1)
			if (close(pipefd[j][1]) == -1)
				perror("in between close");
	}
	/*
	if (close(pipefd[i][1]))
	{
		perror("Close start failed");
		return (free_arg(cmd_args));
	}
	*/
	if (execve(var->cmds[i], cmd_args, NULL) == FAIL)
	{
		perror("Execve failed:");
		return (free_arg(cmd_args));
	}
	close(pipefd[i][0]);
	free_arg(cmd_args);
	return (1);
}

int	outfile_cmd(t_var *var, int **pipefd, int i)
{
	char	**cmd_args;
	int	j;

	j = -1;
	cmd_args = ft_split(var->av[i + 2], ' ');
	dup2(var->file2, STDOUT_FILENO);
	dup2(pipefd[i][0], STDIN_FILENO);
	while (++j < var->size + 1)
	{
		if (j != i)
		{
			if (close(pipefd[j][0]) == -1)
				perror("outfile close 1");
		}
		if (close(pipefd[j][1]) == -1)
		{
			perror("outfile close 2");
		}
	}
	/*
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
	*/
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
	close(pipefd[i][0]);
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
	int		j;
	int		status;

	i = -1;
	j = -1;
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
		//close(pipefd[i][0]);
		//close(pipefd[i][1]);
	}
	while (++j < var->size + 1)
	{
		if (close(pipefd[j][0]) == -1)
			perror("parent close 1");
		if (close(pipefd[j][1]) == -1)
			perror("parent close 2");
	}
	i = -1;
	while (++i < var->size - 1)
		waitpid(pids[i], &status, 0);
	return (1);
}
