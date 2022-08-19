/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 18:24:44 by engooh            #+#    #+#             */
/*   Updated: 2022/07/27 23:17:24 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/// Malloc str && copy la valeur de tmp && return str
char	*ft_init_variable_env(char *tmp)
{
	char	*str;

	if (!tmp)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!str)
		return (NULL);
	ft_memset(str, '\0', ft_strlen(tmp) + 1);
	str = ft_strcpy(str, tmp);
	return (str);
}

/// Ajoute un nouveau node initialisé a la fin de lst. 
void	ft_add_variable_env(char *name, char *value,
			int init_value, t_env **lst_env)
{
	t_env	*new;

	new = ft_lst_env_new(name, value, init_value);
	if (new)
		ft_lst_env_add_back(lst_env, new);
}

/// initialise lst_env depuis l'environement d'origine ///
t_env	*ft_init_env(char **env)
{
	t_env	*lst;
	char	*pwd;
	int		i;

	lst = NULL;
	i = 0;
	pwd = ft_get_pwd();
	ft_lst_setenv("PWD", pwd, 1, &lst);
	free(pwd);
	while (env && env[i])
	{
		ft_parsing_setenv(env[i], &lst);
		i++;
	}
	return (lst);
}
