/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:46:50 by tliot             #+#    #+#             */
/*   Updated: 2022/08/20 20:02:19 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

/*
** ctrl-\ : (SIGQUIT) is received. regenerat the prompt
** ctrl-c : (SIGINT) is receveived. new line + new prompt + clear text
**          for child process no new prompt because is already done by parent
*/

void	parent_signal(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 2);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		(*g_global)->exit_code = 130;
	}
}

void	child_signal(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 2);
		(*g_global)->exit_code = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		(*g_global)->exit_code = 130;
	}
}

void	get_signal(int sig)
{
	if ((*g_global)->pid)
		child_signal(sig);
	else
		parent_signal(sig);
}

void	exit_succes(t_minishell *minishell)
{
	clear_history();
	printf("exit\n");
	ft_exit(minishell);
}
