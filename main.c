/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/07/15 18:04:16 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_init_variable_name_env(char *str, int pos_separator)
{
	char *variable_name;
	
	if(pos_separator != 0)
	{
		variable_name = (char *)malloc(sizeof(char) * pos_separator + 1);
		if(variable_name)
			variable_name = ft_strncpy(variable_name, str, pos_separator);
		else
			return (NULL);
	}
	else
	{
		variable_name = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
		if(variable_name)
			variable_name = ft_strcpy(variable_name, str);
		else
			return (NULL);
	}
	return (variable_name);
}

char *ft_init_variable_value_env(char *str, int pos_separator)
{
	char *variable_value;
	
	if(pos_separator == 0 )
		return (NULL);
	str += pos_separator;
	variable_value = malloc(sizeof(char) * ft_strlen(str) + 1);
	if(variable_value)
		variable_value = ft_strcpy(variable_value, str);
	else
		return (NULL);
	return (variable_value);
}

void	ft_split_variable_env(char *str, t_env	**lst_env)
{
	t_env	*new;

	new = ft_lst_env_new(str);
	if(new)
	{
		ft_lst_env_add_back(lst_env,new);
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
		
		ft_split_variable_env(NULL,&lst);
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
	//lst2 = NULL;
	lst = ft_init_env(env);
	
	lst2 = lst;
	while (lst2)
	{
		/*
		if(lst2->variable_name)
			printf("%s",lst2->variable_name);
		else 
			printf("(NULL)\n");
		*/
		if(lst2->variable_value)
			printf("%s\n",lst2->variable_value);
		else
			printf("(NULL)\n");
		
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