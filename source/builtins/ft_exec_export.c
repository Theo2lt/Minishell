/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 03:44:37 by tliot             #+#    #+#             */
/*   Updated: 2022/07/28 01:02:47 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// PREND tableau de str et lst d'environemment en paramettre
/// AJOUTE a lst les different argument de CMD en prenant 
/// en compte l'etat de init values
/// RETURN 0 si OK sinon 1

int	ft_exec_export(char **cmd, t_env **lst)
{
	int	i;

	i = 1;
	if (!cmd || !cmd[0])
		return (1);
	while (cmd[i])
		ft_parsing_setenv(cmd[i++], lst);
	return (0);
}

int	ft_parsing_export(char *str)
{
	char	*tmp;

	tmp = str;
	if (*tmp == '_' || ft_isalpha(*tmp))
	{
		tmp++;
		while (*tmp)
		{
			if (*tmp == '=')
				break ;
			if ((*tmp == '_' || ft_isalnum(*tmp)))
				tmp++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

////// PARSING A FINIR !!! //////
void	ft_parsing_setenv(char *cmd, t_env **lst)
{
	int		init_value;
	char	**split;

	init_value = 0;
	if (!ft_parsing_export(cmd))
	{
		ft_putstr_fd("bash: export: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(" :invalid\n", 2);
	}
	else
	{
		if (ft_char_set(cmd, '=') != 0)
			init_value = 1;
		split = ft_split(cmd, '=');
		ft_lst_setenv(split[0], split[1], init_value, lst);
		ft_free_tab2(split);
	}
}
