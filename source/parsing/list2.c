/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:52:31 by tliot             #+#    #+#             */
/*   Updated: 2022/08/23 13:52:38 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

static void	recursion(t_def *lst, void (*del)(void *))
{
	if (lst)
		recursion(lst->next, (*del));
	def_lstdelone(lst, (*del));
}

void	def_lstclear(t_def **lst, void (*del)(void *))
{
	if (!lst || !*lst)
		return ;
	recursion(*lst, (*del));
	*lst = NULL;
}
