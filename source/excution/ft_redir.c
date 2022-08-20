/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:19:39 by tliot             #+#    #+#             */
/*   Updated: 2022/08/19 09:24:39 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_r_infile(t_exec *cmd_tmp, int fd_previous)
{
	if (cmd_tmp->infile > 0)
	{
		dup2(cmd_tmp->infile, STDIN_FILENO);
		if (cmd_tmp->infile > 0)
			close(cmd_tmp->infile);
		if (fd_previous > 0)
			close(fd_previous);
	}
	else if (cmd_tmp->num_cmd != 1)
	{
		dup2(fd_previous, STDIN_FILENO);
		if (fd_previous > 0)
			close(fd_previous);
	}
}

void	ft_r_out(t_minishell *minishell, t_exec *cmd_tmp, int *fd)
{
	if (cmd_tmp->outfile > 1)
		dup2(cmd_tmp->outfile, STDOUT_FILENO);
	else if (cmd_tmp->num_cmd != ft_exec_lstsize(minishell->exec))
		dup2(fd[1], STDOUT_FILENO);
	if (ft_exec_lstsize(minishell->exec) > 1 && fd[1] > 0)
		close(fd[1]);
	if (fd[0] > 0)
		close(fd[0]);
}

int	ft_is_dir(char *fileName)
{
	struct stat	path;
	int			res;

	res = stat(fileName, &path);
	if (res != 0)
		return (0);
	if (S_ISDIR(path.st_mode))
		return (1);
	return (0);
}
