/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:38:20 by tliot             #+#    #+#             */
/*   Updated: 2022/07/22 02:20:59 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"


/// PREND tableau de str
/// AFFICHE les arguments en tenant compte du -n
/// RETURN 0 si OK sinon 1

	/// PARSING A FINIR /// avec multi -nnnnnn , voir comportement de bash.
int ft_exec_echo(char **cmd)
{
	int i;

	i = 1;
	if (!cmd || !cmd[i])
	{
		printf("\n");
		return (1);
	}
	if (ft_strcmp(cmd[i], "-n") == 0)
	{
		if (cmd[++i])
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
	return (0);
}
