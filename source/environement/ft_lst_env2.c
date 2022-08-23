/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:09:56 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 15:00:24 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// PREND *name et lst environement en PARAMETRE 
/// RETURN un node de lst si "name = lst->name" et init_value == 0 
t_env	*ft_lst_getexport(char *name, t_env *lst)
{
	while (lst)
	{
		if (lst->init_value == 0)
			if (ft_strcmp(lst->variable_name, name) == 0)
				return (lst);
		lst = lst->next;
	}
	return (NULL);
}

//// Modifie ou crée un node selon l'existance du name dans lst
/// Mofifie ou crée une valeur relier au name et modifie l'etat d'initialisation
void	ft_lst_setenv(char *name, char *value, int init_value, t_env **lst)
{
	t_env	*tmp;

	if (ft_lst_getenv(name, *lst))
	{
		if (init_value == 1)
		{
			tmp = ft_lst_getenv(name, *lst);
			free(tmp->variable_value);
			tmp->variable_value = ft_init_variable_env(value);
		}
	}
	else if (ft_lst_getexport(name, *lst))
	{
		tmp = ft_lst_getexport(name, *lst);
		if (init_value == 1)
			tmp->init_value = 1;
		free(tmp->variable_name);
		tmp->variable_name = ft_init_variable_env(name);
		tmp->variable_value = ft_init_variable_env(value);
	}
	else
		ft_add_variable_env(name, value, init_value, lst);
}

/// Returne la taille de lst
int	ft_lstsize_env(t_env *lst)
{
	int	l;

	l = 0;
	while (lst && ++l)
		lst = lst->next;
	return (l);
}
