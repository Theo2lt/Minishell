/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/07/21 05:43:46 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_init_variable_env(char *tmp)
{
	char *variable_name;
	if(!tmp)
		return (NULL);
	variable_name = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!variable_name)
		return (NULL);
	ft_memset(variable_name, '\0', ft_strlen(tmp) + 1);
	variable_name = ft_strcpy(variable_name, tmp);
	
	return (variable_name);
}

void ft_add_variable_env(char *name ,char *value, int init_value, t_env **lst_env)
{
	t_env *new;
	new = ft_lst_env_new(name,value,init_value);
	if (new)
		ft_lst_env_add_back(lst_env, new);

}

t_env *ft_init_env(char **env)
{
	t_env *lst;
	int i;

	lst = NULL;
	i = 0;
	
	while (env && env[i])
	{
		ft_parsing_setenv(env[i], &lst);
		i++;
	}
	return (lst);
}

char **ft_readline(void)
{
	char *cmd;
	char **cmd_arg;

	cmd_arg = NULL;
	cmd = NULL;
	cmd = readline("BOSH$> ");
	if (cmd[0])
	{
		cmd_arg = ft_split(cmd, ' ');
		add_history(cmd);
		free(cmd);
		return (cmd_arg);
	}

	return (NULL);
}

void ft_exit(t_env *lst)
{
	if (lst)
		ft_lst_env_free(lst);
	exit(0);
}



int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;

	t_env *lst;
	char **cmd;
	
	cmd = NULL;
	lst = ft_init_env(env);
	while (1)
	{
		cmd = ft_readline();
		if(cmd)
		{
			if (ft_strcmp(cmd[0], "echo") == 0)
				ft_exec_echo(cmd);
	
			if (ft_strcmp(cmd[0], "cd") == 0)
				ft_exec_cd(cmd,&lst);
	
			if (ft_strcmp(cmd[0], "pwd") == 0)
				ft_exec_pwd();
	
			if (ft_strcmp(cmd[0], "export") == 0)
				ft_exec_export(cmd,&lst);
	
			if (ft_strcmp(cmd[0], "env") == 0)
				ft_exec_env(lst);

			if (ft_strcmp(cmd[0], "unset") == 0)
				ft_exec_unset(cmd,&lst);

			if (ft_strcmp(cmd[0], "b") == 0)
				ft_lst_env_BUG(lst);

			if (ft_strcmp(cmd[0], "exit") == 0)
			{
				cmd = ft_free_tab(cmd);
				rl_clear_history();
				ft_exit(lst);
			}
			cmd = ft_free_tab(cmd);
		}
	}
	return (0);
}