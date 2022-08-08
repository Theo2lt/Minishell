/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:35:58 by tliot             #+#    #+#             */
/*   Updated: 2022/08/08 13:40:56 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

void ft_put_siganture()
{
	ft_putstr_fd("\n\n       __  __   ___   _  _   ___   ___   _  _   ___   _      _     \n",2);
	ft_putstr_fd("      |  \\/  | |_ _| | \\| | | __| / __| | || | | __| | |    | |    \n",2);
	ft_putstr_fd("      | |\\/| |  | |  | .` | | _|  \\__ \\ | __ | | _|  | |__  | |__  \n",2);
	ft_putstr_fd("      |_|  |_| |___| |_|\\_| |___| |___/ |_||_| |___| |____| |____| \n",2);
	ft_putstr_fd("                                                                    \n",2);
	ft_putstr_fd("                           by engooh & tliot                        \n\n\n",2);
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

void ft_exit(t_minishell *mini)
{
	if (mini->env_lst)
		ft_lst_env_free(mini->env_lst);
	if (mini->cmd_lst)
		ft_sim_cmd_lst_free(mini->cmd_lst);
	free(mini);
	exit(0);
}

t_minishell *ft_init_mini(char **env)
{
	t_minishell *mini;
	
	mini = malloc(sizeof(*mini));
	mini->env_lst = ft_init_env(env);
	mini->cmd_lst = NULL;
	return(mini);
}

/*
void	ft_wait_all_pid(t_cmd *lst)
{
	t_cmd	*lst2;

	lst2 = lst;
	while (lst2)
	{
		waitpid(lst2->pid, NULL, 0);
		lst2 = lst2->next;
	}
}
*/

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell *minishell;
	
	ft_put_siganture();
	minishell = ft_init_mini(env);
	ft_putstr_fd("\n||||||||||   CMD INIT OK   ||||||||||\n",2);
	//ft_sim_cmds_lst_BUG(minishell->cmd_lst);
	ft_execution(minishell);

	ft_wait_all_pid(minishell->cmd_lst);
	ft_sim_cmds_lst_BUG(minishell->cmd_lst);
	ft_put_siganture();

	ft_exit(minishell);
	return (0);
}
