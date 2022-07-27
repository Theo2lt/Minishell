/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:45:51 by tliot             #+#    #+#             */
/*   Updated: 2022/07/28 01:03:33 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_parsing_unset(char *str)
{
	char	*tmp;

	tmp = str;
	if (*tmp == '_' || ft_isalnum(*tmp))
	{
		tmp++;
		while (*tmp)
		{
			if (*tmp == '=')
				break ;
			if ((*tmp == '_' || ft_isalnum(*tmp)))
				tmp++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

/// PREND tableau de str et lst d'environement 
/// SUPPRIME node dans lst si le nom correspond
/// RETURN 0 quand fini

void	ft_exec_unset(char **name, t_env **lst)
{
	int	i;

	i = 1;
	while (name[i] && lst)
	{
		if (!ft_parsing_unset(name[i]))
		{
			ft_putstr_fd("bash: unset: ", 2);
			ft_putstr_fd(name[i], 2);
			ft_putstr_fd(" :invalid\n", 2);
		}
		else
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
