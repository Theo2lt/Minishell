/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 04:43:37 by engooh            #+#    #+#             */
/*   Updated: 2022/08/22 14:02:24 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

t_minishell	**g_global;

void	ft_start(t_minishell	*minishell, char *input)
{
	minishell->exec = parser(input, minishell->env_lst);
	if (minishell->exec)
	{	
		ft_assigne_num_lstexec(minishell->exec);
		if (minishell->exec->tabs_exeve
			&& ft_is_builting(minishell->exec->tabs_exeve[0])
			&& !minishell->exec->next)
			ft_redir_simple_bulting(minishell);
		else
		{
			ft_execution(minishell);
			ft_wait_all_pid(minishell->exec);
		}
		//ft_sim_exec_lst_bug(minishell->begin);
		ft_delete_exec_lst_free(&minishell->exec);
		ft_sim_exec_lst_bug(minishell->begin);
		minishell->exec = NULL;
	}
}

void	ft_launcher(t_minishell	*minishell, char *input)
{
	while (42)
	{
		minishell->pid = 0;
		ft_signal();
		input = readline("Minibosh-22.0$ ");
		if (!input)
			exit_succes(minishell);
		add_history(input);
		if (ft_strcmp(input, "") != 1)
			ft_start(minishell, input);
	}
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
	mini->exit_code = 0;
	mini->pid = 0;
	mini->begin = NULL;
	ft_put_siganture();
	return (mini);
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
	input = NULL;
	ft_launcher(minishell, input);
	return (0);
}
