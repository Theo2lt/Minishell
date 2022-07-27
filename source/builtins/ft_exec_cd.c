/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:40:48 by tliot             #+#    #+#             */
/*   Updated: 2022/07/27 23:22:37 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// PREND tableau de str et lst d'environemment en paramettre
// Modifie $PWD et $OLDPWD quand la fonction est utilisé
// CRÉER $PWD et $OLDPWD si il n'existe pas.
// RETURN 0 si OK sinon 1 

void	ft_put_err(char *cmd, char *arg, char *strerrno)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerrno, 2);
	ft_putstr_fd("\n", 2);
}

int	ft_exec_cd_oldpwd(char **cmd, t_env **lst)
{
	if (!ft_lst_getenv("OLDPWD", *lst))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (0);
	}
	if (chdir(ft_lst_getenv("OLDPWD", *lst)->variable_value) != 0)
	{
		ft_put_err("cd", cmd[1], strerror(errno));
		return (0);
	}
	printf("%s\n", ft_lst_getenv("OLDPWD", *lst)->variable_value);
	return (1);
}

int ft_exec_cd_home(char **cmd, t_env **lst)
{
	if (!ft_lst_getenv("HOME", *lst))
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (0);
	}
	if (chdir(ft_lst_getenv("HOME", *lst)->variable_value) != 0)
	{
		ft_put_err("cd", cmd[1], strerror(errno));
		return (0);
	}
	return (1);
}

int	ft_exec_cd_many_arg(char *cmd)
{
	ft_putstr_fd("bash: cd: too many arguments: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	ft_exec_cd(char **cmd, t_env **lst)
{
	char	*pwd;

	if (ft_tablen(cmd) > 2)
		return (ft_exec_cd_many_arg(cmd[1]));
	else if (cmd[1] && cmd[1][0] == '-' )
	{
		if (!ft_exec_cd_oldpwd(cmd, lst))
			return (0);
	}
	else if (!cmd[1] || cmd[1][0] == '~')
	{
		if (!ft_exec_cd_oldpwd(cmd, lst))
			return (0);
	}
	else if (chdir(cmd[1]) != 0)
	{
		ft_put_err("cd", cmd[1], strerror(errno));
		return (0);
	}
	ft_lst_setenv("OLDPWD", ft_lst_getenv("PWD",*lst)->variable_value, 1, lst);
	pwd = ft_get_pwd();
	ft_lst_setenv("PWD", pwd, 1, lst);
	free(pwd);
	return (0);
}
