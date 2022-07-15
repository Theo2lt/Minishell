/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 02:25:09 by tliot             #+#    #+#             */
/*   Updated: 2022/07/15 05:01:32 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env	*ft_lst_env_new(void)
{
	t_env	*new;

	new = (t_env*)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->variable_name = NULL;
	new->variable_value = NULL;
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