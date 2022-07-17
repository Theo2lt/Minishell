/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/07/17 15:50:47 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_init_variable_name_env(char *str, int pos_separator)
{
	char *variable_name;

	variable_name = NULL;

	if (pos_separator != 0)
	{
		variable_name = (char *)malloc(sizeof(char) * (pos_separator + 2));
		if (!variable_name)
			return (NULL);
		ft_memset(variable_name, '\0', pos_separator + 2);
		variable_name = ft_strncpy(variable_name, str, pos_separator + 1);
	}
	else
	{
		variable_name = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		if (!variable_name)
			return (NULL);
		ft_memset(variable_name, '\0', ft_strlen(str) + 1);
		variable_name = ft_strcpy(variable_name, str);
	}
	return (variable_name);
}

char *ft_init_variable_value_env(char *str, int pos_separator)
{
	char *variable_value;

	if (pos_separator == 0)
		return (NULL);
	str += pos_separator + 1;
	variable_value = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (variable_value)
		variable_value = ft_strcpy(variable_value, str);
	else
		return (NULL);
	return (variable_value);
}

void ft_add_variable_env(char *str, t_env **lst_env)
{
	t_env *new;
	new = ft_lst_env_new(str);
	if (new)
		ft_lst_env_add_back(lst_env, new);
}

t_env *ft_init_env(char **env)
{
	t_env *lst;
	int i;

	lst = NULL;
	i = 0;

	if (!env[0])
	{
		ft_add_variable_env("OLDPWD=", &lst);
		ft_add_variable_env("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin", &lst);
		ft_add_variable_env("HOME=/home", &lst);
	}
	while (env[i])
	{
		// printf("DEBUG : %s\n",env[i]);
		ft_add_variable_env(env[i], &lst);
		i++;
	}

	/*
	ft_split_variable_env(NULL,&lst);
	ft_split_variable_env("BB = B",&lst);
	ft_split_variable_env("AA = B",&lst);
	*/
	return (lst);
}

char **ft_readline(void)
{
	char *cmd;
	char **cmd_arg;

	cmd_arg = NULL;
	cmd = NULL;
	cmd = readline("BOSH$ ");
	if (cmd)
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
	(void)env;

	t_env *lst;
	char **cmd;
	cmd = NULL;
	
	lst = ft_init_env(env);
	while (1)
	{
		cmd = ft_readline();
		if (ft_strcmp(cmd[0], "echo") == 0)
			ft_exec_echo(cmd);

		if (ft_strcmp(cmd[0], "cd") == 0)
			ft_exec_cd(cmd,lst);

		if (ft_strcmp(cmd[0], "pwd") == 0)
			ft_exec_pwd();

		if (ft_strcmp(cmd[0], "export") == 0)
			ft_exec_export(cmd[1],&lst);

		if (ft_strcmp(cmd[0], "env") == 0)
			ft_exec_env(lst);

		if (ft_strcmp(cmd[0], "exit") == 0)
		{
			cmd = ft_free_tab(cmd);
			rl_clear_history();
			ft_exit(lst);
		}
		cmd = ft_free_tab(cmd);
	}

	return (0);
}