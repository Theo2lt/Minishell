/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/07/27 04:44:31 by tliot            ###   ########.fr       */
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
	pid_t   pid;
	char **cmd;
	cmd = NULL;

	lst = ft_init_env(env);
	while (1)
	{
		cmd = ft_readline();
		if(cmd)
		{
			if(!ft_manage_builting(cmd,&lst))
			{
				pid = fork();
				if(pid == 0)
					ft_exec(lst,cmd);
				waitpid(pid, NULL, 0);
			}
			cmd = ft_free_tab2(cmd);
		}
	}
	return (0);
}
