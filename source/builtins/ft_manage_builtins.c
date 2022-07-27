/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:31:17 by tliot             #+#    #+#             */
/*   Updated: 2022/07/27 23:32:13 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_is_builting(char *cmd)
{
	if (!ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd"))
		return (1);
	else
		return (0);
}

int	ft_manage_builting(char **cmd, t_env **lst)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_exec_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_exec_cd(cmd, lst);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_exec_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_exec_export(cmd, lst);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_exec_env(*lst);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_exec_unset(cmd, lst);
	else if (ft_strcmp(cmd[0], "b") == 0)
		ft_lst_env_BUG(*lst);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		cmd = ft_free_tab2(cmd);
		rl_clear_history();
		ft_exit(*lst);
	}
	else
		return (0);
	return (1);
}
