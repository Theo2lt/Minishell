/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tockenisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engooh <engooh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 17:57:49 by engooh            #+#    #+#             */
/*   Updated: 2022/07/31 19:09:53 by engooh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

int	set_infile(char *str, t_exec *exec)
{
	if (exec->infile > 0)
	{
		exec->infile = open(str, O_RDONLY, 0666);
		if (exec->infile < 0)
			ft_putstr_fd("ERROR INFILE", 2);
	}
	if (exec->infile < 0)
		return (0);
	return (1);
}

int	set_outfile(char *str, t_exec *exec, int mode)
{
	if (mode && exec->outfile >= 0)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (exec->outfile < 0)
			ft_putstr_fd("ERROR OUFILE", 2);
	}
	else if (!mode && exec->outfile >= 0)
	{
		exec->outfile = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (exec->outfile < 0)
			ft_putstr_fd("ERROR OUFILE", 2);
	}
	if (exec->outfile < 0)
		return (0);
	return (1);
}
/*int	set_cmd(char *str, t_exec *exec)
{

}

int	set_arg(char *str, t_exec *exec)
{

}

t_exec	*tocken(char *str)
{
	int	file;
	int	redir;
	int	cmd;
	int	arg;


	while (*str)
	{

	}
}*/
