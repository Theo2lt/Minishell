/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:51:40 by engooh            #+#    #+#             */
/*   Updated: 2022/08/15 21:35:06 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/*
void	ft_print_env(t_env *env, int i)
{
	if (env)
	{
		if (env->next)
		{
			ft_print_env(env->next, i + 1);
			printf(
				"nbr node %d - curente node %p - next node 
				%p\nname node %s - value node %s - \n\n",
				i, env, env->next, env->variable_name, env->variable_value);
		}
	}
}
*/

char	*ft_getenv(t_env *env, char *str, int len)
{
	if (env && !ft_strncmp(env->variable_name, str, len)
		&& ft_strlen(env->variable_name) == (size_t)len)
		return (env->variable_value);
	else if (env && env->next)
		return (ft_getenv(env->next, str, len));
	return (NULL);
}

t_env	*ft_lst_new(void)
{
	t_env	*p;

	p = malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->next = NULL;
	return (p);
}

void	ft_push_env(t_env *lst, char *str)
{
	char	*s;

	if (!lst || !str)
		return ;
	if (!str)
	{
		lst->variable_name = NULL;
		lst->variable_value = NULL;
		return ;
	}
	s = ft_strchr(str, '=');
	lst->variable_name = ft_substr(str, 0, s - str);
	lst->variable_value = ft_substr(s + 1, 0, ft_strlen(s));
}

void	ft_delete_env(t_env *lst, char *str)
{
	if (!lst)
		return ;
	(void)str;
	if ((lst)->variable_name)
		free((lst)->variable_name);
	if ((lst)->variable_value)
		free((lst)->variable_value);
	if (lst)
		free(lst);
}

void	ft_converte_tab_list(char **tab, t_env **lst,
		void (f)(t_env *lst, char *str))
{
	if ((tab && *tab) || (*lst && (*lst)->next))
	{
		if (!*lst)
			*lst = ft_lst_new();
		if (!tab)
			ft_converte_tab_list(NULL, &((*lst)->next), f);
		if (tab)
			ft_converte_tab_list(tab + 1, &((*lst)->next), f);
	}
	if (tab)
		f(*lst, *tab);
	if (!tab)
		f(*lst, NULL);
}
