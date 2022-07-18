/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:44:37 by tliot             #+#    #+#             */
/*   Updated: 2022/07/18 03:44:42 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_export(char *cmd, t_env **lst)
{
	t_env *lst2;

	lst2 = *lst;
	if (!cmd)
	{
		printf("-- export affichage pas encore  -- \n");
		while (lst2)
		{
			if (lst2->init_value == 0)
				printf("%s\n", lst2->variable_name);
			lst2 = lst2->next;
		}
	}
	else
		ft_parsing_setenv(cmd, lst);
	return (0);
}
