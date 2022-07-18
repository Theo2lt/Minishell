/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_unsetpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:45:51 by tliot             #+#    #+#             */
/*   Updated: 2022/07/18 04:19:25 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exec_unset(char *name, t_env **lst)
{
	t_env *tmp;
	t_env *lst2;
	
	lst2 = *lst;
	tmp = ft_lst_getenv(name, *lst);
	while(tmp && lst2)
	{
		if(tmp == lst2)
		{
			lst2 = lst2->next;
			*lst = lst2;
			if (tmp->variable_name)
				free(tmp->variable_name);
			if (tmp->variable_value)
				free(tmp->variable_value);
			free(tmp);
			break;
		}
		if(lst2->next == tmp)
		{
			lst2->next = &(*tmp->next);
			if (tmp->variable_name)
				free(tmp->variable_name);
			if (tmp->variable_value)
				free(tmp->variable_value);
			free(tmp);
			break;
		}
		lst2 = lst2->next;
	}
}