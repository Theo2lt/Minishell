/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:40:48 by tliot             #+#    #+#             */
/*   Updated: 2022/07/18 03:41:03 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_cd(char **cmd, t_env *lst)
{
	char *pwd;

	pwd = ft_get_pwd();
	if (cmd[1][0] == '-')
	{
		if (chdir(ft_lst_getenv("OLDPWD", lst)->variable_value) != 0) // A GERER SANS ENVIRONMENT
		{
			printf("err OLDPWD\n");
			free(pwd);
			return (1);
		}
		printf("%s\n", ft_lst_getenv("OLDPWD", lst)->variable_value);
	}
	else if (cmd[1][0] == '~')
	{
		if (chdir(ft_lst_getenv("HOME", lst)->variable_value) != 0)
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
	ft_lst_setenv("OLDPWD", pwd, 1, &lst);
	free(pwd);
	return (0);
}