/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/08/08 19:21:46 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"


t_exec	*ft_delete_exec(t_exec *exec)
{
	if (exec)
	{
		if (exec->infile > 0)
			close(exec->infile);
		if (exec->outfile > 1)
			close(exec->outfile);
		if (exec->args)
			free(exec->args);
		if (exec->tabs_exeve)
			ft_free_tab2(exec->tabs_exeve);
		if (exec->next)
			ft_delete_exec(exec->next);
		if (exec)
			free(exec);
		return (NULL);
	}
	return (NULL);
}


void	ft_delete_exec_lst_free(t_exec **lst)
{
	t_exec	*lst2;

	while (*lst)
	{
		lst2 = *lst;
		*lst = (*lst)->next;
		if (lst2->infile > 0)
			close(lst2->infile);
		if (lst2->outfile > 1)
			close(lst2->outfile);
		if (lst2->tabs_exeve)
			lst2->tabs_exeve = ft_free_tab2(lst2->tabs_exeve);
		if (lst2->args)
			free(lst2->args);
		free(lst2);
		lst2 = NULL;
	}
}
void ft_put_siganture()
{
	ft_putstr_fd("\n\n       __  __   ___   _  _   ___   ___   _  _   ___   _      _     \n",2);
	ft_putstr_fd("      |  \\/  | |_ _| | \\| | | __| / __| | || | | __| | |    | |    \n",2);
	ft_putstr_fd("      | |\\/| |  | |  | .` | | _|  \\__ \\ | __ | | _|  | |__  | |__  \n",2);
	ft_putstr_fd("      |_|  |_| |___| |_|\\_| |___| |___/ |_||_| |___| |____| |____| \n",2);
	ft_putstr_fd("                                                                    \n",2);
	ft_putstr_fd("                           by engooh & tliot                        \n\n\n",2);
}

void ft_exit(t_minishell *mini)
{
	if (mini->env_lst)
		ft_lst_env_free(mini->env_lst);
	if (mini->exec)
		ft_delete_exec_lst_free(&mini->exec);
	if (mini)
		free(mini);
	exit(0);
}

t_minishell *ft_init_mini(char **env)
{
	t_minishell *mini;
	
	mini = malloc(sizeof(*mini));
	mini->env_lst = ft_init_env(env);
	mini->exec = NULL;
	return(mini);
}

int main(int argc, char **argv, char **env)
{
	t_minishell *minishell;
	char *input;

	(void)argc;
	(void)argv;
	
	minishell = ft_init_mini(env);
	ft_put_siganture();
	while (42)
	{
		input = readline("minishell> ");
		add_history(input);
		if(ft_strcmp(input, "exit") == 0)
		{
				ft_exit(minishell);
				exit(0);
		}
		minishell->exec = parser(input, minishell->env_lst);
		ft_sim_exec_lst_BUG(minishell->exec);
		ft_execution(minishell);
		ft_wait_all_pid(minishell->exec);
		ft_delete_exec_lst_free(&minishell->exec);
	}
	//ft_put_siganture();
	printf("here\n");
	ft_exit(minishell);
	return (0);
}
