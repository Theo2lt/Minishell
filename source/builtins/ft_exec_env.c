/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:39:14 by tliot             #+#    #+#             */
/*   Updated: 2022/07/27 23:22:50 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// PREND lst d'environement 
/// AFFICHE tout l'environement de lst
/// RETURN 0 quand fini

int	ft_exec_env(t_env *lst)
{
	while (lst)
	{
		if (lst->init_value == 1)
		{
			if (lst->variable_value)
				printf("%s=%s\n", lst->variable_name, lst->variable_value);
			if (!lst->variable_value)
				printf("%s=\n", lst->variable_name);
		}
		lst = lst->next;
	}
	return (0);
}
