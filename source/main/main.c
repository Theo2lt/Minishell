/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/08/21 05:44:56 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

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

void	ft_put_siganture(void)
{
	ft_putstr_fd("\n\n       __  __   ___   _  _   ___", 2);
	ft_putstr_fd("   ___   _  _   ___   _      _     \n", 2);
	ft_putstr_fd("      |  \\/  | |_ _| | \\| | | __| ", 2);
	ft_putstr_fd("/ __| | || | | __| | |    | |    \n", 2);
	ft_putstr_fd("      | |\\/| |  | |  | .` | | _|  \\", 2);
	ft_putstr_fd("\\__\\ | __ | | _|  | |__  | |__  \n", 2);
	ft_putstr_fd("      |_|  |_| |___| |_|\\_| |___| |", 2);
	ft_putstr_fd("___/ |_||_| |___| |____| |____| \n", 2);
	ft_putstr_fd("                                    ", 2);
	ft_putstr_fd("                                \n", 2);
	ft_putstr_fd("                           by engooh", 2);
	ft_putstr_fd(" & tliot                        \n\n\n", 2);
}

t_minishell	*ft_init_mini(void)
{
	t_minishell	*mini;

	mini = malloc(sizeof(*mini));
	mini->env_lst = NULL;
	mini->exec = NULL;
	mini->fd[0] = 0;
	mini->fd[1] = 1;
	mini->fd_previous = 0;
	mini->exit_code = 60;
	ft_put_siganture();
	return (mini);
}

t_minishell	**g_global;

void	sighandler(int sig)
{
	signal(sig, SIG_IGN);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		*input;

	(void)argc;
	(void)argv;
	minishell = ft_init_mini();
	g_global = &minishell;
	minishell->env_lst = ft_init_env(env);
	signal(SIGINT, sighandler);
	while (42)
	{
		input = readline("bosh-5.0$ ");
		add_history(input);
		if (ft_strcmp(input, "") != 1)
		{
			minishell->exec = parser(input, minishell->env_lst);
			if (minishell->exec)
			{	
				ft_assigne_num_lstexec(minishell->exec);
				if (minishell->exec->tabs_exeve && ft_is_builting(minishell->exec->tabs_exeve[0]) && !minishell->exec->next)
					ft_redir_simple_bulting(minishell);
				else
				{
					ft_execution(minishell);
					ft_wait_all_pid(minishell->exec);
				}
				ft_delete_exec_lst_free(&minishell->exec);
				minishell->exec = NULL;
			}
			else
				(*g_global)->exit_code = 2;
		}
	}
	return (0);
}
