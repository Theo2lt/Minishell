/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expende.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:49:47 by engooh            #+#    #+#             */
/*   Updated: 2022/07/26 16:42:23 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

	if (!lst)
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

void	ft_print_env(t_env *env, int i)
{
	if (env)
	{
		if (env->next)
		{
			ft_print_env(env->next, i + 1);
			printf("nbr node %d - curente node %p - next node %p\nname node %s - value node %s - \n\n", i, env, env->next, env->variable_name, env->variable_value);
		}
	}
}

void	ft_converte_tab_list(char **tab, t_env **lst,
		void (f)(t_env *lst, char *str))
{
	if (tab && *tab)
	{
		if (!*lst)
			*lst = ft_lst_new();
		f(*lst, *tab);
		ft_converte_tab_list(tab + 1, &((*lst)->next), f);
	}
}
