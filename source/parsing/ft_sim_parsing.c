/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sim_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 01:29:37 by tliot             #+#    #+#             */
/*   Updated: 2022/07/29 06:09:30 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

char **ft_pars_cmd_cmdarg_sim()
{
    char *cmd;
    char **cmd_arg;
    cmd = readline("cmd > ");
    if (cmd[0])
	{
		cmd_arg = ft_split(cmd, ' ');
		free(cmd);
		return (cmd_arg);
	}
    return (NULL);
}

t_cmd	*ft_init_sim_cmd()
{
    t_cmd *cmds;
    cmds = NULL;
    ft_sim_cmd_add(ft_pars_cmd_cmdarg_sim(),"filea","fileb", &cmds);
    ft_sim_cmd_add(ft_pars_cmd_cmdarg_sim(),"filea","fileb", &cmds);
    ft_sim_cmd_add(ft_pars_cmd_cmdarg_sim(),NULL,NULL, &cmds);
    ft_sim_cmd_add(ft_pars_cmd_cmdarg_sim(),"filea","fileb", &cmds);
    return (cmds);
}