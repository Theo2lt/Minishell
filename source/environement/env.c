/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:24:44 by engooh            #+#    #+#             */
/*   Updated: 2022/07/22 18:49:11 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char	*ft_init_variable_env(char *tmp)
{
	char	*variable_name;

	if (!tmp)
		return (NULL);
	variable_name = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!variable_name)
		return (NULL);
	ft_memset(variable_name, '\0', ft_strlen(tmp) + 1);
	variable_name = ft_strcpy(variable_name, tmp);
	return (variable_name);
}

void	ft_add_variable_env(char *name, char *value, int init_value,
	t_env **lst_env)
{
	t_env	*new;

	new = ft_lst_env_new(name, value, init_value);
	if (new)
		ft_lst_env_add_back(lst_env, new);
}

////// PARSING A FINIR !!! //////
void	ft_parsing_setenv(char *cmd, t_env **lst)
{
	int	init_value;
	char	**split;
	
	init_value = 0;
	if(ft_char_set(cmd,'=') != 0)
		init_value = 1;
	split = ft_split(cmd,'=');
	ft_lst_setenv(split[0],split[1],init_value,lst);
	ft_free_tab((void **)split);	
}

t_env	*ft_init_env(char **env)
{
	t_env	*lst;
	int		i;

	i = 0;
	lst = NULL;
	while (env && env[i])
	{
		ft_parsing_setenv(env[i], &lst);
		i++;
	}
	return (lst);
}
