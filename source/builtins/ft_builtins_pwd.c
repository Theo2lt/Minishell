/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:37:14 by tliot             #+#    #+#             */
/*   Updated: 2022/08/15 12:41:47 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*ft_get_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	return (pwd);
}

int	ft_builtin_pwd(void)
{
	char	*pwd;

	pwd = ft_get_pwd();
	if (!pwd)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",2);
		(*g_global)->exit_code = 1;
	}
	else
	{
		printf("%s\n", pwd);
		(*g_global)->exit_code = 0;
	}
	free(pwd);
	return (0);
}