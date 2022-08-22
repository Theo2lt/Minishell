/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:51:06 by tliot             #+#    #+#             */
/*   Updated: 2022/08/21 17:26:16 by tliot            ###   ########.fr       */
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

void	ft_commande_not_found(char	**cmd)
{
	char	*tmp;

	tmp = NULL;
	if (cmd && *cmd)
		tmp = ft_joint_3str("bash: ", *cmd, ": command not found\n");
	else
		tmp = ft_joint_3str("bash: ", "", ": command not found\n");
	ft_putstr_fd(tmp, 2);
	free(tmp);
}

void	ft_commande_error(char	**cmd, char *str_error)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_joint_3str(": ", str_error, "\n");
	tmp2 = ft_joint_3str("bash: ", cmd[0], tmp);
	write(2, tmp2, ft_strlen(tmp2));
	free(tmp);
	free(tmp2);
}
