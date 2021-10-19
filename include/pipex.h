/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:07:09 by rcollas           #+#    #+#             */
/*   Updated: 2021/10/18 15:28:15 by rcollas          ###   ########.fr       */
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
	int		ac;
	char	**path;
	char	**av;
	char	*cmds;
	char	**env;
	pid_t	*pids;
}			t_var;

char	**get_binaries_path(char **env);
void	add_slash(t_var *var);
void	init_var(t_var *var, char **av, char **env, int ac);
void	proceed_pipes(t_var *var, int **pipefd, int i);
int		free_arg(char **cmd_args);
int		get_cmds(t_var *var, int k);
int		exec(t_var *var, int **pipefd, pid_t *pids);
int		free_pipes(int **pipefd, t_var *var);
int		check_cmds(t_var *var, char **cmd_args, int i, int k);
int		close_pipes(int **pipefd, t_var *var);
int		init_pipefd(t_var *var, int ***pipefd);
int		init_pid(pid_t **pids, t_var *var);

#endif
