/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:46:55 by tliot             #+#    #+#             */
/*   Updated: 2022/08/19 18:03:08 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_builting_exit_check_arg(char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			tmp = ft_joint_3str("bash: exit: ",
					cmd[1], "numeric argument required\n");
			ft_putstr_fd(tmp, 2);
			free(tmp);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_builting_exit(char **cmd, t_minishell *mini)
{	
	if (!cmd[1])
		(*g_global)->exit_code = 0;
	else if (!ft_builting_exit_check_arg(cmd))
		(*g_global)->exit_code = 2;
	else if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		(*g_global)->exit_code = 1;
	}
	else
		(*g_global)->exit_code = ft_atoi((const char *)cmd[1]);
	ft_exit(mini);
}

void	ft_all_close_fd(void)
{
	int	i;

	i = 0;
	while (i <= 1024)
	{
		if (i != 2)
			close(i);
		i++;
	}
}

void	ft_exit(t_minishell *mini)
{
	int	exit_code;

	exit_code = (*g_global)->exit_code;
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
