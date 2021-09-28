/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:07:09 by rcollas           #+#    #+#             */
/*   Updated: 2021/09/27 08:34:51 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define FAIL 0
# define SUCCESS 1

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_var {
	int		file1;
	int		file2;
	int		size;
	char	**path;
	char	**av;
	char	**cmds;
	char	**env;
	pid_t	*pids;
}			t_var;

char	**get_binaries_path(char **env);
void	add_slash(t_var *var);
int		free_arg(char **cmd_args);
int		get_cmds(t_var *var);
int		exec(t_var *var, int **pipefd, pid_t *pids);
int		proceed_pipes(t_var *var, int **pipefd, int i);
int		free_pipes(int **pipefd, t_var *var);
int		check_cmds(t_var *var);

#endif
