/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:40:48 by tliot             #+#    #+#             */
/*   Updated: 2022/08/15 21:10:45 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// PREND tableau de str et lst d'environemment en paramettre
// Modifie $PWD et $OLDPWD quand la fonction est utilisé
// CRÉER $PWD et $OLDPWD si il n'existe pas.
// RETURN 0 si OK sinon 1 

void	ft_put_err_cd(char *cmd, char *arg, char *strerrno)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerrno, 2);
	ft_putstr_fd("\n", 2);
	(*g_global)->exit_code = 1;
}

void	ft_exec_cd_oldpwd(char **cmd, t_env **lst)
{
	if (!ft_lst_getenv("OLDPWD", *lst))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		(*g_global)->exit_code = 1;
	}
	else if (chdir(ft_lst_getenv("OLDPWD", *lst)->variable_value) != 0)
	{
		ft_put_err_cd("cd", cmd[1], strerror(errno));
		(*g_global)->exit_code = 1;
	}
	else
	{
		printf("%s\n", ft_lst_getenv("OLDPWD", *lst)->variable_value);
		(*g_global)->exit_code = 0;
	}
}

void	ft_exec_cd_home(char **cmd, t_env **lst)
{
	if (!ft_lst_getenv("HOME", *lst))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		(*g_global)->exit_code = 1;
	}
	else if (chdir(ft_lst_getenv("HOME", *lst)->variable_value) != 0)
	{
		ft_put_err_cd("cd", cmd[1], strerror(errno));
		(*g_global)->exit_code = 1;
	}
	else
		(*g_global)->exit_code = 0;
}

void	ft_exec_cd_many_arg(char *cmd)
{
	char	*tmp;

	tmp = ft_joint_3str("bash: cd: too many arguments: ", cmd, "\n");
	ft_putstr_fd(tmp, 2);
	free(tmp);
	(*g_global)->exit_code = 1;
}

void	ft_builtin_cd(char **cmd, t_env **lst)
{
	char	*pwd;

	if (ft_tablen(cmd) > 2)
		return (ft_exec_cd_many_arg(cmd[1]));
	else if (cmd[1] && !ft_strcmp(cmd[1], "-" ))
		ft_exec_cd_oldpwd(cmd, lst);
	else if (!cmd[1] || !ft_strcmp(cmd[1], "~" ))
		ft_exec_cd_home(cmd, lst);
	else if (chdir(cmd[1]) != 0)
		ft_put_err_cd("cd", cmd[1], strerror(errno));
	else
		(*g_global)->exit_code = 0;
	pwd = ft_get_pwd();
	ft_lst_setenv("OLDPWD", ft_lst_getenv("PWD",*lst)->variable_value, 1, lst);
	if (!pwd)
	{
		ft_lst_setenv("PWD", cmd[1], 1, lst);
		ft_putstr_fd("chdir: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: No such file or directory\n", 2);
	}
	else
		ft_lst_setenv("PWD", pwd, 1, lst);
	free(pwd);
}
