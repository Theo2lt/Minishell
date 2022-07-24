/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:40:48 by tliot             #+#    #+#             */
/*   Updated: 2022/07/23 23:16:24 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

// PREND tableau de str et lst d'environemment en paramettre
// Modifie $PWD et $OLDPWD quand la fonction est utilisé
// CRÉER $PWD et $OLDPWD si il n'existe pas.
// RETURN 0 si OK sinon 1

int ft_exec_cd(char **cmd, t_env **lst)
{
	char *pwd;

	pwd = ft_get_pwd();
	ft_lst_setenv("PWD", pwd, 1, lst);
	if(ft_tablen(cmd) > 2)
	{
		ft_putstr_fd("cd: string not in pwd: ",2);
		ft_putstr_fd(cmd[1],2);
		ft_putstr_fd("\n",2);
		return (1);
	}
	if (cmd[1] && cmd[1][0] == '-' )
	{
		if (!ft_lst_getenv("OLDPWD", *lst))
		{
			ft_putstr_fd("cd: OLDPWD not set\n",2);
			free(pwd);
			return (1);
		}
		if (chdir(ft_lst_getenv("OLDPWD", *lst)->variable_value) != 0)
		{
			ft_putstr_fd("err OLDPWD\n",2);
			free(pwd);
			return (1);
		}
		printf("%s\n", ft_lst_getenv("OLDPWD", *lst)->variable_value);
	}
	else if (!cmd[1] || cmd[1][0] == '~')
	{
		if (!ft_lst_getenv("HOME", *lst))
		{
			ft_putstr_fd("cd: HOME not set\n",2);
			free(pwd);
			return (1);
		}
		if (chdir(ft_lst_getenv("HOME", *lst)->variable_value) != 0)
		{
			ft_putstr_fd("bash: cd: no such file or directory: ~ \n", 2);
			free(pwd);
			return (1);
		}
	}
	else if (chdir(cmd[1]) != 0)
	{
		ft_putstr_fd("bash: cd: no such file or directory: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("\n", 2);
		free(pwd);
		return (1);
	}
	ft_lst_setenv("OLDPWD", pwd, 1, lst);
	free(pwd);
	return (0);
}