/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:46:04 by tliot             #+#    #+#             */
/*   Updated: 2022/08/22 15:08:55 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_delete_exec_lst_free(t_exec **lst)
{
	t_exec	*lst2;

	if (!*lst)
		return ;
	while (*lst)
	{
		lst2 = *lst;
		*lst = (*lst)->next;
		if (lst2->infile > 0)
			close(lst2->infile);
		if (lst2->outfile > 1)
			close(lst2->outfile);
		if (lst2->tabs_exeve)
			lst2->tabs_exeve = ft_free_tab2(lst2->tabs_exeve);
		if (lst2->args)
			free(lst2->args);
		free(lst2);
		lst2 = NULL;
	}
	(*g_global)->begin = NULL;
}

void	ft_signal(void)
{
	signal(SIGINT, get_signal);
	signal(SIGQUIT, get_signal);
	signal(SIGTSTP, SIG_IGN);
}
