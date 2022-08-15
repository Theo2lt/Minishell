/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:51:06 by tliot             #+#    #+#             */
/*   Updated: 2022/08/15 21:23:12 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	ft_exec_lstsize(t_exec *lst)
{
	int	l;

	l = 0;
	while (lst && ++l)
		lst = lst->next;
	return (l);
}

int	ft_assigne_num_lstexec(t_exec *lst)
{
	int	l;

	l = 0;
	while (lst && ++l)
	{
		lst->num_cmd = l;
		lst = lst->next;
	}
	return (l);
}
