/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:38:20 by tliot             #+#    #+#             */
/*   Updated: 2022/08/13 10:06:19 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Minishell.h"


/// PREND tableau de str
/// AFFICHE les arguments en tenant compte du -n
/// RETURN 0 si OK sinon 1

	/// PARSING A FINIR /// avec multi -nnnnnn , voir comportement de bash.


int ft_check_parsing_echo(char *cmd)
{
	int	i;
	
	i = 3;
	if(!ft_strncmp(cmd,"-n",2))
	{
		while (cmd[i])
		{
			if(cmd[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
	
}






int ft_exec_echo(char **cmd)
{
	int	i;

	i = 1;
	if (!cmd || !cmd[i])
	{
		printf("\n");
		return (1);
	}
	if (ft_check_parsing_echo(cmd[i]))
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
