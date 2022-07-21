/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:40:48 by tliot             #+#    #+#             */
/*   Updated: 2022/07/21 05:12:26 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_putstr("cd: string not in pwd: ",2);
		ft_putstr(cmd[1],2);
		ft_putstr("\n",2);
		return (1);
	}
	if (cmd[1] && cmd[1][0] == '-' )
	{
		if (!ft_lst_getenv("OLDPWD", *lst))
		{
			ft_putstr("cd: OLDPWD not set\n",2);
			free(pwd);
			return (1);
		}
		if (chdir(ft_lst_getenv("OLDPWD", *lst)->variable_value) != 0)
		{
			ft_putstr("err OLDPWD\n",2);
			free(pwd);
			return (1);
		}
		printf("%s\n", ft_lst_getenv("OLDPWD", *lst)->variable_value);
	}
	else if (!cmd[1] || cmd[1][0] == '~')
	{
		if (!ft_lst_getenv("HOME", *lst))
		{
			ft_putstr("cd: HOME not set\n",2);
			free(pwd);
			return (1);
		}
		if (chdir(ft_lst_getenv("HOME", *lst)->variable_value) != 0)
		{
			ft_putstr("bash: cd: no such file or directory: ~ \n", 2);
			free(pwd);
			return (1);
		}
	}
	else if (chdir(cmd[1]) != 0)
	{
		ft_putstr("bash: cd: no such file or directory: ", 2);
		ft_putstr(cmd[1], 2);
		ft_putstr("\n", 2);
		free(pwd);
		return (1);
	}
	ft_lst_setenv("OLDPWD", pwd, 1, lst);
	
	free(pwd);
	return (0);
}