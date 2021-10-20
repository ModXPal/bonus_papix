/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 08:14:11 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/20 10:31:12 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	free_arg(char **cmd_args)
{
	int	i;

	i = -1;
	while (cmd_args[++i])
		free(cmd_args[i]);
	free(cmd_args);
	return (0);
}

int	free_pipes(int **pipefd, t_var *var)
{
	int	i;

	i = -1;
	while (++i < var->size)
		free(pipefd[i]);
	free(pipefd);
	return (0);
}
