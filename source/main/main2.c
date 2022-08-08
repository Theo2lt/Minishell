/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/08/08 12:58:31 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


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
				cmd = ft_free_tab2(cmd);
				rl_clear_history();
				ft_exit(lst);
			}
			cmd = ft_free_tab2(cmd);
		}
	}
	return (0);
}
