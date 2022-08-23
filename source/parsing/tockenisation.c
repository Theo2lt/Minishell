/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:57:49 by engooh            #+#    #+#             */
/*   Updated: 2022/08/23 13:46:40 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	*ft_delete_exec(t_exec *exec)
{
	if (exec)
	{
		if (exec->tabs_exeve)
			ft_free_tab2(exec->tabs_exeve);
		if (exec->args)
			free(exec->args);
		if (exec->infile)
			close(exec->infile);
		if (exec->outfile)
			close(exec->outfile);
		free(exec);
		exec = NULL;
	}
	return (NULL);
}

void	*ft_delete_execs(t_exec *exec)
{
	if (exec)
		if (exec->next)
			ft_delete_execs(exec->next);
	return (ft_delete_exec(exec));
}

void	ft_positive_negative(char *str, int signe)
{
	if (!str)
		return ;
	while (*str)
	{
		if (*str && signe > 0 && *str < 0)
			*str *= -1;
		if (*str && signe < 0 && *str > 0)
			*str *= -1;
		str++;
	}
}

void	ft_print_error_file(char *str, char *sterr)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(sterr, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_exit_child(t_minishell *mini, int exit_code)
{
	ft_delete_execs(mini->begin);
	if (mini->env_lst)
		ft_lst_env_free(mini->env_lst);
	if (mini->exec)
		ft_delete_exec_lst_free(&mini->exec);
	if (mini->fd[1] > 1)
		close(mini->fd[1]);
	if (mini->fd[0] > 0)
		close(mini->fd[0]);
	if (mini->fd_previous > 0)
		close(mini->fd_previous);
	if (mini)
		free(mini);
	ft_all_close_fd();
	exit(exit_code);
}
