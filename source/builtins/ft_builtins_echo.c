/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:38:20 by tliot             #+#    #+#             */
/*   Updated: 2022/08/16 14:23:24 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// PREND tableau de str
/// AFFICHE les arguments en tenant compte du -n
/// RETURN 0 si OK sinon 1

int	ft_check_parsing_echo(char **cmd)
{
	int	i;
	int	j;

	j = 1;
	i = 1;
	while (cmd[j])
	{
		if (!ft_strncmp(cmd[j], "-n", 2))
		{
			while (cmd[j][i])
			{
				if (cmd[j][i] != 'n')
					return (j);
				i++;
			}
		}
		else
			break ;
		i = 1;
		j++;
	}
	return (j);
}

void	ft_builtin_echo(char **cmd)
{
	int	i;

	i = 1;
	i = ft_check_parsing_echo(cmd);
	if (i != 1)
	{
		if (cmd[i])
			printf("%s", cmd[i++]);
		while (cmd[i])
			printf(" %s", cmd[i++]);
	}
	else
	{
		if (cmd[i])
			printf("%s", cmd[i++]);
		while (cmd[i])
			printf(" %s", cmd[i++]);
		printf("\n");
	}
	(*g_global)->exit_code = 0;
}
