/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:31:17 by tliot             #+#    #+#             */
/*   Updated: 2022/08/17 13:54:25 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_is_builting(char *cmd)
{
	if (!cmd)
		return (0);
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

void	ft_redir_simple_bulting(t_minishell *minishell)
{
	/*
	int		f_stdout;

	f_stdout = dup(STDOUT_FILENO);
	if (minishell->exec->outfile > 1)
	{
		dup2(minishell->exec->outfile, STDOUT_FILENO);
		ft_manage_builting(minishell->exec->tabs_exeve, minishell);
		dup2(f_stdout, STDOUT_FILENO);
		close(minishell->exec->outfile);
	}
	if (f_stdout > 1)
		close(f_stdout);
	if (minishell->exec->infile > 0)
		close(minishell->exec->infile);
	if (minishell->exec->outfile > 0)
		close(minishell->exec->outfile);
	*/
	ft_manage_builting(minishell->exec->tabs_exeve, minishell);
}

int	ft_manage_builting(char **cmd, t_minishell *minishell)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		ft_builtin_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		ft_builtin_cd(cmd, &(minishell->env_lst));
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_builtin_pwd();
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_builtin_export(cmd, &(minishell->env_lst));
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_builtin_env(minishell->env_lst);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_builtin_unset(cmd, &(minishell->env_lst));
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		rl_clear_history();
		printf("exit\n");
		ft_builting_exit(cmd, minishell);
	}
	else
		return (0);
	return (1);
}
