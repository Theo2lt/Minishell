/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FT_BUG.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 12:10:42 by tliot             #+#    #+#             */
/*   Updated: 2022/08/21 12:13:32 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void	ft_lst_env_bug(t_env *lst)
{
	while (lst)
	{
		printf("\n---------------------------------\n");
		printf(" < &NOEUD > addr : %p \n", lst);
		printf("---------------------------------\n");
		printf("addr : %p | %s\n", lst->variable_name, lst->variable_name);
		printf("addr : %p | %d\n", &lst->init_value, lst->init_value);
		printf("addr : %p | %s\n", lst->variable_value, lst->variable_value);
		printf("addr : %p | lst->next\n", lst->next);
		printf("---------------------------------\n");
		lst = lst->next;
	}
}

void	ft_sim_exec_lst_bug(t_exec *lst)
{
	int	i;
	int	y;

	while (lst)
	{
		y = -1;
		i = 1;
		printf("\n-------------CMD-------------\n");
		if (!lst->args)
			printf("addr : %p | CMD_ARG (NULL) \n", lst->args);
		else
		{	
			printf("addr : %p |    CMD_ARG : ", lst->tabs_exeve);
			while (lst->tabs_exeve[++y])
				printf("[%s]", lst->tabs_exeve[y]);
			printf("\n");
			y = 0;
		}
		printf("addr : %p |     in_fd : %d\n", &lst->infile, lst->infile);
		printf("addr : %p |    out_fd : %d\n", &lst->outfile, lst->outfile);
		printf("addr : %p | lst->next\n", lst->next);
		printf("---------------------------------\n");
		lst = lst->next;
		i++;
	}
}
