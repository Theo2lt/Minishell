/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_unsetpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:45:51 by tliot             #+#    #+#             */
/*   Updated: 2022/07/27 23:30:41 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// PREND tableau de str et lst d'environement 
/// SUPPRIME node dans lst si le nom correspond
/// RETURN 0 quand fini

void	ft_exec_unset(char **name, t_env **lst)
{
	int	i;

	i = 1;
	while (name[i] && lst)
	{
		ft_unset(name[i], lst);
		i++;
	}
}

/// PREND  str et lst d'environement 
/// SUPPRIME node dans lst si le nom correspond
/// FREE le node a supprimé
void	ft_unset(char *name, t_env **lst)
{
	t_env	*tmp;
	t_env	*lst2;

	lst2 = *lst;
	tmp = ft_lst_getenv(name, *lst);
	while (tmp && lst2)
	{
		if (tmp == lst2)
		{
			lst2 = lst2->next;
			*lst = lst2;
			tmp->next = NULL;
			break ;
		}
		if (lst2->next == tmp)
		{
			lst2->next = &(*tmp->next);
			tmp->next = NULL;
			break ;
		}
		lst2 = lst2->next;
	}
	if (tmp)
		ft_lst_env_free(tmp);
}
