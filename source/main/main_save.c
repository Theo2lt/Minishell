/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_save.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/07/29 00:31:08 by tliot            ###   ########.fr       */
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

void ft_exit(t_minishell *mini)
{
	if (mini->env_lst)
		ft_lst_env_free(mini->env_lst);
	free(mini);
	exit(0);
}

t_minishell *ft_init_mini(char **env)
{
	t_minishell *mini;
	
	mini = (t_minishell *) malloc(sizeof(t_minishell *));
	mini->env_lst = ft_init_env(env);
	mini->cmd_lst = NULL;
	return(mini);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell *minishell;

	minishell = ft_init_mini(env);
	pid_t   pid;
	char **cmd;
	cmd = NULL;
	
	
	ft_putstr_fd("\n\n       __  __   ___   _  _   ___   ___   _  _   ___   _      _     \n",2);
	ft_putstr_fd("      |  \\/  | |_ _| | \\| | | __| / __| | || | | __| | |    | |    \n",2);
	ft_putstr_fd("      | |\\/| |  | |  | .` | | _|  \\__ \\ | __ | | _|  | |__  | |__  \n",2);
	ft_putstr_fd("      |_|  |_| |___| |_|\\_| |___| |___/ |_||_| |___| |____| |____| \n",2);
	ft_putstr_fd("                                                                    \n",2);
	ft_putstr_fd("                           by engooh & tliot                        \n\n\n",2);


	while (1)
	{
		cmd = ft_readline();
		if(cmd)
		{
			if(!ft_manage_builting(cmd,minishell))
			{
				pid = fork();
				if(pid == 0)
					ft_exec(minishell->env_lst,cmd);
				waitpid(pid, NULL, 0);
			}
			cmd = ft_free_tab2(cmd);
		}
	}
	return (0);
}