/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 05:36:19 by engooh            #+#    #+#             */
/*   Updated: 2022/07/13 05:58:21 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../../include/Minishell.h"

t_env	*ft_lstnew(void *content)
{
	t_env	*p;

	p = malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->next = NULL;
	p->content = content;
	return (p);
}

int	ft_lstsize(t_env *lst)
{
	int	l;

	l = 0;
	while (lst && ++l)
		lst = lst->next;
	return (l);
}

static void	recursion(t_env *lst, void (*del)(void *))
{
	if (lst)
		recursion(lst->next, (*del));
	ft_lstdelone(lst, (*del));
}

void	ft_lstclear(t_env **lst, void (*del)(void *))
{
	if (!lst || !*lst)
		return ;
	recursion(*lst, (*del));
	*lst = NULL;
}

void	ft_lstadd_back(t_env **alst, t_env *new)
{
	if (*alst)
	{
		if ((*alst)->next)
			ft_lstadd_back(&((*alst)->next), new);
		else
			(*alst)->next = new;
	}
	else
		*alst = new;
}

void	ft_lstadd_front(t_env **alst, t_env *new)
{
	new->next = &(**alst);
	*alst = new;
}

void	ft_lstdelone(t_env *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}


void	ft_lstiter(t_env *lst, void (*f)(void *))
{
	if (lst && f)
		f(lst->content);
	if (lst && lst->next)
		ft_lstiter(lst->next, f);
}
