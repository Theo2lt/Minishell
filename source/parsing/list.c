/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:09:37 by engooh            #+#    #+#             */
/*   Updated: 2022/07/23 18:08:20 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_def	*def_lstnew(void *content)
{
	t_def	*p;

	p = malloc(sizeof(t_list));
	if (!p)
		return (NULL);
	p->next = NULL;
	return (p);
}

void	def_lstadd_back(t_def **alst, t_def *new)
{
	if (*alst)
	{
		if ((*alst)->next)
			def_lstadd_back(&((*alst)->next), new);
		else
			(*alst)->next = new;
	}
	else
		*alst = new;
}

/* CES FONCTION VONT NOUS SERVIRE A MANIPULER 
   N'IMPORTE QU'ELLES TYPE DE LISTE CHAINE */

t_def	*def_lstlast(t_def *lst)
{
	if (lst && lst->next)
		return (def_lstlast(lst->next));
	return (lst);
}

void	def_lstiter(t_def *lst, void (*f)(void *))
{
	if (lst && f)
		f(lst->content);
	if (lst && lst->next)
		def_lstiter(lst->next, f);
}

void	def_lstdelone(t_def *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst);
	free(lst);
}

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
