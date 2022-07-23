/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expende.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 17:49:47 by engooh            #+#    #+#             */
/*   Updated: 2022/07/23 19:26:38 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	*ft_copy_malloc(void *var_env)
{
	char	*s;

	s = ft_substr(var_env, 0, ft_strlen(var_env));
	if (!s)
		return (NULL);
	return (s);
}

void	ft_converte_tab_list(char **tab, t_def *list, void (*f)(void *))
{
	if (*tab)
	{
		list->content = ft_copy_malloc(*tab);
		def_lstnew()
		ft_converte_tab_list(&(*tab++), ft_list, f);
	}
}
