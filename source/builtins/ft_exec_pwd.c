/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:37:14 by tliot             #+#    #+#             */
/*   Updated: 2022/07/22 02:21:14 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// AFFICHE PWD 
/// RETURN 0 si OK sinon 1

int ft_exec_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

/// RETURN char *pwd sinon null
/// AFFICHE si error perror("getcwd");
char *ft_get_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (pwd);
}