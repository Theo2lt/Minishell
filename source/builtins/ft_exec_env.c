/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:39:14 by tliot             #+#    #+#             */
/*   Updated: 2022/07/22 02:21:03 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// PREND lst d'environement 
/// AFFICHE tout l'environement de lst
/// RETURN 0 quand fini

int ft_exec_env(t_env *lst)
{
	while (lst)
	{
		if (lst->init_value == 1)
			printf("%s=%s\n", lst->variable_name, lst->variable_value);
		lst = lst->next;
	}
	return (0);
}
