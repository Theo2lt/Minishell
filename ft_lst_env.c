/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 02:25:09 by tliot             #+#    #+#             */
/*   Updated: 2022/07/15 17:10:06 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	*ft_lst_env_new(char *str)
{
	t_env	*new;
	int pos_separator;
	
	pos_separator = ft_char_set(str, '=') + 1;
	new = (t_env*)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->variable_name = ft_init_variable_name_env(str, pos_separator);
	new->variable_value = ft_init_variable_value_env(str, pos_separator);
	new->next = NULL;
	return (new);
}

t_env	*ft_lst_env_last(t_env *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lst_env_add_back(t_env **alst, t_env *new)
{
	t_env	*last;

	if (*alst)
	{
		last = ft_lst_env_last(*alst);
		last->next = new;
	}
	else
		*alst = new;
}

void	ft_lst_env_free(t_env *lst)
{
	t_env	*lst2;

	while (lst)
	{
		lst2 = lst;
		lst = lst->next;
		if (lst2->variable_name)
			free(lst2->variable_name);
		if (lst2->variable_value)
			free(lst2->variable_value);
		free(lst2);
	}
}