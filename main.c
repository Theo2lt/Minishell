/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/07/15 16:38:12 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	ft_split_variable_env(char *str, t_env	**lst_env)
{
	t_env	*new;
	int pos_separator;

	new = NULL;
	pos_separator = ft_char_set(str, '=') + 1;
	new = ft_lst_env_new();
	if(new)
	{
		if(pos_separator != 0)
		{
			new->variable_name = malloc(sizeof(char) * pos_separator + 1);
			if(new->variable_name)
				new->variable_name = ft_strncpy(new->variable_name, str, pos_separator);
			else
				new->variable_name = NULL;
			str += pos_separator;
			new->variable_value = malloc(sizeof(char) * ft_strlen(str) + 1);
			if(new->variable_value)
				new->variable_value = ft_strcpy(new->variable_value, str);
			else
				new->variable_value = NULL;
			ft_lst_env_add_back(lst_env,new);
		}
		else
		{
			new->variable_name = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
			new->variable_name = ft_strcpy(new->variable_name, str);
			new->variable_value = NULL;
			ft_lst_env_add_back(lst_env,new);
		}
	}
}

t_env	*ft_init_env(char **env)
{
	t_env	*lst;
	int		i;

	lst = NULL;
	i = 0;
	if(!env[0])
	{
		
		//env[0] = ft_strjoin("OLDPWD=",ft_get_pwd());
		//env[1] = "";
	}
	while (env[i])
	{
		ft_split_variable_env(env[i],&lst);
		i++;
	}
	return (lst);
}

int main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	(void) env;
	t_env	*lst;
	t_env	*lst2;
	
	lst = NULL;
	lst2 = NULL;
	lst = ft_init_env(env);
	lst2 = lst;
	while (lst2)
	{
		if(lst2->variable_name)
			printf("%s\n",lst2->variable_name);
		lst2 = lst2->next;
	}
	if(lst)
		ft_lst_env_free(lst);
	
	/*
	if(!env[0])
		printf("NULL\n");
	env[0] = "OLDPWD=/";
	printf("%s\n",env[0]);
	
	ft_exec_pwd();
	ft_exec_cd("/home");
	ft_exec_pwd();
	ft_exec_cd("-");
	ft_exec_pwd();
	ft_exec_cd("-");
	ft_exec_pwd();
	if(ft_strcmp(argv[1], "echo") == 0)
		ft_exec_echo(argv);
		
	if(ft_strcmp(argv[1], "cd") == 0)
		ft_exec_cd(argv[2]);
		
	if(ft_strcmp(argv[1], "pwd") == 0)
		ft_exec_pwd();
	ft_exec_pwd();
	printf("la : %s\n",env[0]);
	*/
	return (0);
}