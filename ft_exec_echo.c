/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:38:20 by tliot             #+#    #+#             */
/*   Updated: 2022/07/18 03:38:21 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int ft_exec_echo(char **cmd) // GERER LES -NNNNNNNNNNNNN N INFINI // A REFAIRE CAR C'EST TRES MOCHE
{
	int i;

	i = 1;
	if (!cmd[i])
	{
		printf("\n");
		return (1);
	}
	if (ft_strcmp(cmd[i], "echo") == 0 && ft_strcmp(cmd[i + 1], "-n") == 0)
	{
		i = 3;
		if (cmd[i] && i == 3)
			printf("%s", cmd[i++]);
		while (cmd[i])
			printf(" %s", cmd[i++]);
	}
	else if (ft_strcmp(cmd[i], "echo") == 0)
	{
		i = 2;
		if (cmd[i] && i == 2)
			printf("%s", cmd[i++]);
		while (cmd[i])
			printf(" %s", cmd[i++]);
		printf("\n");
	}
	return (0);
}
