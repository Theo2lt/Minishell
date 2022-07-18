/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:39:14 by tliot             #+#    #+#             */
/*   Updated: 2022/07/18 03:54:47 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exec_env(t_env *lst)
{
	while (lst)
	{
		if (lst->init_value == 1)
			printf("%s=%s\n", lst->variable_name, lst->variable_value);
		lst = lst->next;
	}

	return (0);
}

void ft_parsing_setenv(char *cmd, t_env **lst)
{
	int init_value;
	char **split;
	
	init_value = 0;
	if(ft_char_set(cmd,'=') != 0)
		init_value = 1;
	split = ft_split(cmd,'=');
	ft_lst_setenv(split[0],split[1],init_value,lst);
	ft_free_tab(split);
}