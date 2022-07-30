/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sim_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 01:29:37 by tliot             #+#    #+#             */
/*   Updated: 2022/07/30 05:25:02 by tliot            ###   ########.fr       */
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
    char *rep;
    rep = " ";
    cmds = NULL;
    int i;

    i = 0;
    while (i < 1000)
    {
        ft_sim_cmd_add(ft_split(rep,' '),"filea","fileb", &cmds);
        ft_sim_cmd_add(ft_split(rep,' '),"filea",NULL, &cmds);
        ft_sim_cmd_add(ft_split(rep,' '),NULL,NULL, &cmds);
        ft_sim_cmd_add(ft_split(rep,' '),NULL,"fileb", &cmds);
        ft_sim_cmd_add(ft_split(rep,' '),NULL,"filec", &cmds);
        i++;
    }
    

    return (cmds);
}